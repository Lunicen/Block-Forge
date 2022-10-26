#include "ChunkPlacer.h"

#include <ppl.h>

#include "Structure/ChunkMeshUtils.h"

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

void ChunkPlacer::RemoveChunkAt(const Position origin)
{
	
}

/*void ChunkPlacer::BuildNewChunks() const
{
	if (_chunksQueueMutex.try_lock())
	{
		auto chunk =  std::move(_newChunksQueue.back());

		const auto origin = chunk.first;
		auto blocks = std::move(chunk.second);

		//_loadedChunks.emplace(std::make_pair<Position, std::unique_ptr<Chunk>>(origin, std::move(chunk)));
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			if (_freeChunks.empty()) 
			{
				_chunksQueueMutex.unlock();
				return;
			}

			

			_loadedChunks[origin] = std::move(chunk);
		}

		_newChunksQueue.pop_back();

		_loadedChunks[origin]->LoadBlocks(blocks);
		_loadedChunks[origin]->LoadMesh(mesh);

		

		_chunksQueueMutex.unlock();
	}
}*/

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

void ChunkPlacer::UpdateChunksAround(const Position& normalizedOrigin)
{
	const auto currentChunksOrigins = _order->GetChunksAround(normalizedOrigin);

	RemoveStaleChunks(currentChunksOrigins);
	AddNewChunks(currentChunksOrigins);
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
		UpdateChunksAround(currentNormalizedPosition);

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(const std::shared_ptr<WorldGenerator>& generator, const size_t chunkSize)
{
	_generator = generator;

	const auto& chunksToGenerate =  _order->GetChunksAmount();

	_freeChunks.reserve(chunksToGenerate);
	_loadedChunks.reserve(chunksToGenerate);

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

void ChunkPlacer::Terminate()
{
	_generator = nullptr;
}
