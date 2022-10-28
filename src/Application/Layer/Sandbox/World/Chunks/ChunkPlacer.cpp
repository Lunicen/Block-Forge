#include "ChunkPlacer.h"

#include <ppl.h>

#include "Structure/ChunkMeshUtils.h"

std::mutex ChunkPlacer::_chunksMutex;

std::vector<std::unique_ptr<Chunk>> ChunkPlacer::_freeChunks = {};
std::unordered_map<Position, std::unique_ptr<Chunk>> ChunkPlacer::_loadedChunks = {};
Position ChunkPlacer::_previousNormalizedPosition = {};
bool ChunkPlacer::_running = false;

std::shared_ptr<WorldGenerator> ChunkPlacer::_generator = nullptr;
std::unique_ptr<Order> ChunkPlacer::_order = nullptr;

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

	const auto mesh = ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap());
	//std::lock_guard<std::mutex> lock(_chunksQueueMutex);

	auto chunk = std::move(_freeChunks.back());
	_freeChunks.pop_back();

	chunk->Load(chunkBlocks, mesh);

	_loadedChunks[origin] = std::move(chunk);
	_log.Trace("Added chunk: " + PositionToString(origin));
}

void ChunkPlacer::AddNewChunks(const std::vector<Position>& currentChunksOrigins)
{
	const auto chunkSize = _order->GetChunkSize();
	
	for(const auto& origin : currentChunksOrigins)
	{
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			BuildChunkAt(origin, chunkSize, _generator);
		}
	}
}

void ChunkPlacer::RemoveStaleChunks(const std::vector<Position>& currentChunksOrigins)
{
	for (auto chunksIterator = _loadedChunks.begin(); chunksIterator != _loadedChunks.end();)
	{
		const auto origin = chunksIterator->first;

		if (std::find(currentChunksOrigins.begin(), currentChunksOrigins.end(), origin) == currentChunksOrigins.end())
		{
			auto handledChunk = std::move(_loadedChunks[origin]);
			chunksIterator = _loadedChunks.erase(chunksIterator);

			_freeChunks.emplace_back(std::move(handledChunk));
		}
		else
		{
			++chunksIterator;
		}
	}
}

void ChunkPlacer::LazyLoader()
{
	auto lastRememberedPosition = _previousNormalizedPosition;

	//while (_running)
	{
		const auto currentChunksOrigins = _order->GetChunksAround(lastRememberedPosition);

		// Remove stale chunks
		for (auto chunksIterator = _loadedChunks.begin(); chunksIterator != _loadedChunks.end();)
		{
			const auto origin = chunksIterator->first;

			if (std::find(currentChunksOrigins.begin(), currentChunksOrigins.end(), origin) == currentChunksOrigins.end())
			{
				const std::lock_guard<std::mutex> lock(_chunksMutex);

				auto handledChunk = std::move(_loadedChunks[origin]);
				chunksIterator = _loadedChunks.erase(chunksIterator);

				_freeChunks.emplace_back(std::move(handledChunk));
			}
			else
			{
				++chunksIterator;
			}
		}


		// Add new chunks
		const auto size = _order->GetChunkSize();
	
		for(const auto& origin : currentChunksOrigins)
		{
			if (_loadedChunks.find(origin) == _loadedChunks.end())
			{
				//BuildChunkAt(origin, chunkSize, _generator);
				const auto chunkFrame = ChunkFrame{origin, size};

				ChunkBlocks chunkBlocks;
				chunkBlocks.resize(size * size * size);
				
				_generator->PaintChunk(chunkFrame, chunkBlocks);

				const auto mesh = ChunkMeshUtils::GetMeshVertices(chunkFrame, chunkBlocks, _generator->GetBlockMap());


				const std::lock_guard<std::mutex> lock(_chunksMutex);

				auto chunk = std::move(_freeChunks.back());
				_freeChunks.pop_back();

				chunk->Load(chunkBlocks, mesh);

				_loadedChunks[origin] = std::move(chunk);
			}
		}

		// Here should be implemented wait functionality
		// That would wait for the conditional variable
	}
}

void ChunkPlacer::UpdateChunksAround(const Position& normalizedOrigin)
{
	

	
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

void ChunkPlacer::ReactToCameraMovement(const Position& position)
{
	const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;
		//UpdateChunksAround(currentNormalizedPosition);

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(const std::shared_ptr<WorldGenerator>& generator, const size_t chunkSize)
{
	if (_generator != nullptr)
	{
		while (!_loadedChunks.empty())
		{
			_loadedChunks.erase(_loadedChunks.begin());
		}

		while (!_freeChunks.empty())
		{
			_freeChunks.erase(_freeChunks.begin());
		}
	}

	_generator = generator;

	const auto& chunksToGenerate = _order->GetChunksAmount();

	_freeChunks.reserve(chunksToGenerate);
	_loadedChunks.reserve(chunksToGenerate);

	for (size_t i = 0; i < chunksToGenerate; ++i)
	{
		_freeChunks.emplace_back(std::make_unique<Chunk>(chunkSize, _generator->GetBlockMap()));
	}

	_running = true;
	_lazyLoader = std::make_unique<std::thread>(&LazyLoader);
}

std::mutex& ChunkPlacer::GetMutex()
{
	return _chunksMutex;
}

std::unordered_map<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks()
{
	return _loadedChunks;
}

void ChunkPlacer::Terminate()
{
	_generator = nullptr;
}
