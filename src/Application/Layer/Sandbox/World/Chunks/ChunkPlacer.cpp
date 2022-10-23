#include "ChunkPlacer.h"

#include <ppl.h>

#include "Structure/ChunkMeshUtils.h"

std::vector<std::future<void>> ChunkPlacer::_futures = {};
std::vector<std::future<void>> ChunkPlacer::_globalFutures = {};
std::shared_ptr<WorldGenerator> ChunkPlacer::_generator = nullptr;
std::vector<std::tuple<ChunkFrame, ChunkBlocks, std::vector<Vertex>>> ChunkPlacer::_chunksToBuildQueue = {};
std::vector<Position> ChunkPlacer::_chunksToRemoveQueue = {};
std::unique_ptr<Order> ChunkPlacer::_order = {};
std::unordered_map<Position, std::unique_ptr<Chunk>> ChunkPlacer::_loadedChunks = {};
std::mutex ChunkPlacer::_buildQueueMutex;
std::mutex ChunkPlacer::_cleanupFuturesMutex;

Position ChunkPlacer::GetNormalizedPosition(const Point3D& position, const size_t& chunkSize) const
{
	auto normalizedPosition = position;

	normalizedPosition /= chunkSize;

	normalizedPosition.x = floor(normalizedPosition.x);
	normalizedPosition.y = floor(normalizedPosition.y);
	normalizedPosition.z = floor(normalizedPosition.z);

	return {normalizedPosition};
}

std::string ChunkPlacer::PositionToString(const Position& position) const
{
	return std::to_string(position.x) + ", " + 
		   std::to_string(position.y) + ", " + 
		   std::to_string(position.z);
}

void ChunkPlacer::BuildChunkAt(
	const Position origin,
	const size_t size,
	const std::shared_ptr<WorldGenerator>& generator)
{
	const auto chunkFrame = ChunkFrame{origin, size};

	ChunkBlocks chunkBlocks;
	chunkBlocks.resize(size * size * size);
	
	generator->PaintChunk(chunkFrame, chunkBlocks);

	std::lock_guard<std::mutex> lock(_buildQueueMutex);
	_chunksToBuildQueue.emplace_back(std::tuple<ChunkFrame, ChunkBlocks, std::vector<Vertex>>(
		ChunkFrame{origin, size}, 
		chunkBlocks, 
		ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap())));
}

void ChunkPlacer::BuildChunksInQueue() const
{
	_buildQueueMutex.lock();
	const auto chunkData = _chunksToBuildQueue.back();
	_chunksToBuildQueue.pop_back();
	_buildQueueMutex.unlock();

	const auto& frame = std::get<0>(chunkData);
	const auto& blocks = std::get<1>(chunkData);
	const auto& meshVertices = std::get<2>(chunkData);

	_loadedChunks[frame.origin] = std::make_unique<Chunk>(frame, blocks, _generator->GetBlockMap(), meshVertices);
	_log.Trace("Added chunk: " + PositionToString(frame.origin));
}

void ChunkPlacer::RemoveChunksInQueue() const
{
	const auto position = _chunksToRemoveQueue.back();
	_chunksToRemoveQueue.pop_back();

	_loadedChunks.erase(position);
	_log.Trace("Removed chunk: " + PositionToString(position));
}

void ChunkPlacer::AddNewChunksAround(const Position normalizedOrigin)
{
	const auto currentChunksOrigins = _order->GetChunksAround(normalizedOrigin);
	const auto chunkSize = _order->GetChunkSize();

	std::lock_guard<std::mutex> lock(_cleanupFuturesMutex);
	
	for(const auto& origin : currentChunksOrigins)
	{
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			_futures.emplace_back(std::async(std::launch::async, BuildChunkAt, origin, chunkSize, _generator));
		}
	}
}

void ChunkPlacer::RemoveStaleChunksAround(const Position normalizedOrigin)
{
	const auto currentChunksOrigins = _order->GetChunksAround(normalizedOrigin);

	for (const auto& chunkData : _loadedChunks)
	{
		const auto origin = chunkData.first;
		if (std::find(currentChunksOrigins.begin(), currentChunksOrigins.end(), origin) == currentChunksOrigins.end())
		{
			_chunksToRemoveQueue.emplace_back(origin);
		}
	}
}

void ChunkPlacer::CleanupStaleFutures()
{
	if (_cleanupFuturesMutex.try_lock())
	{
		if (!_futures.empty() && _futures.back()._Is_ready())
		{
			_futures.pop_back();
		}
		_cleanupFuturesMutex.unlock();
	}
}

void ChunkPlacer::UpdateChunksAround(const Position& normalizedOrigin)
{
	_globalFutures.emplace_back(std::async(std::launch::async, RemoveStaleChunksAround, normalizedOrigin));
	_globalFutures.emplace_back(std::async(std::launch::async, AddNewChunksAround, normalizedOrigin));

	for(auto globalFuture = _globalFutures.begin(); globalFuture != _globalFutures.end();)
	{ 
		if(globalFuture->_Is_ready())
		{
			globalFuture = _globalFutures.erase(globalFuture); 
		}
		else
		{
			++globalFuture;
		}
	}
}

ChunkPlacer::ChunkPlacer(const OrderType orderType, const size_t chunkSize, const size_t renderDistance, const Position& initPosition)
{
	switch (orderType)
	{
	case OrderType::cube:	
		_order = std::make_unique<CubeOrder>(renderDistance, chunkSize);
		break;

	case OrderType::diamond: 
		_order = std::make_unique<DiamondOrder>(renderDistance, chunkSize);
		break;

	case OrderType::tiltedCube:	
		_order = std::make_unique<TiltedCubeOrder>(renderDistance, chunkSize);
		break;
	}

	_previousNormalizedPosition = GetNormalizedPosition(initPosition, chunkSize);
}

void ChunkPlacer::Update(const Position& position)
{
	if (!_chunksToBuildQueue.empty())
	{
		BuildChunksInQueue();
	}

	if (!_chunksToRemoveQueue.empty())
	{
		RemoveChunksInQueue();
	}

	CleanupStaleFutures();

	const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;
		UpdateChunksAround(currentNormalizedPosition);

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(std::shared_ptr<WorldGenerator> generator) const
{
	_generator = std::move(generator);
	UpdateChunksAround(_previousNormalizedPosition);
}

std::unordered_map<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks()
{
	return _loadedChunks;
}

void ChunkPlacer::Terminate()
{
	while (!_globalFutures.empty())
	{ 
		if(_globalFutures.back()._Is_ready())
		{
			_globalFutures.pop_back();
		}
	}

	while (!_futures.empty())
	{
		CleanupStaleFutures();
	}

	_generator = nullptr;
}
