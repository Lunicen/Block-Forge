#include "ChunkPlacer.h"

#include <ppl.h>

#include "Structure/ChunkMeshUtils.h"

std::vector<std::future<void>> ChunkPlacer::_futures = {};
std::vector<std::future<void>> ChunkPlacer::_globalFutures = {};
std::shared_ptr<WorldGenerator> ChunkPlacer::_generator = nullptr;
std::vector<std::tuple<Position, ChunkBlocks, std::vector<Vertex>>> ChunkPlacer::_newChunksQueue = {};
std::vector<Position> ChunkPlacer::_staleChunksQueue = {};
std::unique_ptr<Order> ChunkPlacer::_order = {};
std::unordered_map<Position, std::unique_ptr<Chunk>> ChunkPlacer::_loadedChunks = {};
std::vector<std::unique_ptr<Chunk>> ChunkPlacer::_freeChunks = {};
std::mutex ChunkPlacer::_chunksQueueMutex;
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

	std::lock_guard<std::mutex> lock(_chunksQueueMutex);
	_newChunksQueue.emplace_back(origin, chunkBlocks, ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap()));
}

void ChunkPlacer::BuildNewChunks() const
{
	if (_chunksQueueMutex.try_lock())
	{
		const auto chunkData = _newChunksQueue.back();

		const auto origin = std::get<0>(chunkData);
		const auto blocks = std::get<1>(chunkData);
		const auto mesh = std::get<2>(chunkData);

		//_loadedChunks.emplace(std::make_pair<Position, std::unique_ptr<Chunk>>(origin, std::move(chunk)));
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			if (_freeChunks.empty()) 
			{
				_chunksQueueMutex.unlock();
				return;
			}

			auto chunk = std::move(_freeChunks.back());
			_freeChunks.pop_back();

			_loadedChunks[origin] = std::move(chunk);
		}

		_newChunksQueue.pop_back();

		_loadedChunks[origin]->LoadBlocks(blocks);
		_loadedChunks[origin]->LoadMesh(mesh);

		_log.Trace("Added chunk: " + PositionToString(origin));

		_chunksQueueMutex.unlock();
	}
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

void ChunkPlacer::RemoveStaleChunks() const
{
	if (_chunksQueueMutex.try_lock())
	{
		const auto origin = _staleChunksQueue.back();
		_staleChunksQueue.pop_back();

		auto chunk = std::move(_loadedChunks[origin]);
		_loadedChunks.erase(origin);

		_freeChunks.emplace_back(std::move(chunk));

		_log.Trace("Added chunk: " + PositionToString(origin));
		_chunksQueueMutex.unlock();
	}
}

void ChunkPlacer::RemoveStaleChunksAround(const Position normalizedOrigin)
{
	const auto currentChunksOrigins = _order->GetChunksAround(normalizedOrigin);

	std::lock_guard<std::mutex> lock(_chunksQueueMutex);

	for (const auto& chunk : _loadedChunks)
	{
		const auto origin = chunk.first;
		if (std::find(currentChunksOrigins.begin(), currentChunksOrigins.end(), origin) == currentChunksOrigins.end())
		{
			_staleChunksQueue.emplace_back(origin);
		}
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

void ChunkPlacer::Update() const
{
	if (!_newChunksQueue.empty())
	{
		BuildNewChunks();
	}

	if (!_staleChunksQueue.empty())
	{
		RemoveStaleChunks();
	}

	CleanupStaleFutures();
}

void ChunkPlacer::ReactToCameraMovement(const Position& position)
{
	const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;
		UpdateChunksAround(currentNormalizedPosition);

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(std::shared_ptr<WorldGenerator> generator, const size_t chunkSize) const
{
	_generator = std::move(generator);

	const auto& chunksToGenerate =  _order->GetChunksAmount();

	_freeChunks.reserve(chunksToGenerate);
	_newChunksQueue.reserve(chunkSize);

	for (size_t i = 0; i < chunksToGenerate; ++i)
	{
		_freeChunks.emplace_back(std::make_unique<Chunk>(chunkSize, _generator->GetBlockMap()));
	}

	UpdateChunksAround(_previousNormalizedPosition);
}

std::unordered_map<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks()
{
	return _loadedChunks;
}

std::mutex& ChunkPlacer::GetMutex()
{
	return _chunksQueueMutex;
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
