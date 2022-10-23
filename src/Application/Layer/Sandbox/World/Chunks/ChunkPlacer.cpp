#include "ChunkPlacer.h"

std::vector<Position> ChunkPlacer::Subtract(const std::vector<Position>& aSet, const std::vector<Position>& bSet)
{
	std::vector<Position> result;

	for (const auto& value : aSet)
	{
		if (std::find(bSet.begin(), bSet.end(), value) == bSet.end())
		{
			result.emplace_back(value);
		}
	}

	return result;
}

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

std::mutex BuildQueueMutex;

void ChunkPlacer::RemoveStaleChunks(const std::vector<Position>& currentChunksOrigins)
{
	std::vector<Position> staleChunksOrigins;

	for (const auto& chunkData : _loadedChunks)
	{
		const auto origin = chunkData.first;
		if (std::find(currentChunksOrigins.begin(), currentChunksOrigins.end(), origin) == currentChunksOrigins.end())
		{
			staleChunksOrigins.emplace_back(origin);
		}
	}

	for (const auto& origin : staleChunksOrigins)
	{
		_log.Trace("Removed chunk: " + PositionToString(origin));
		_loadedChunks.erase(origin);
	}

	_log.Debug("Finished removing stale chunks!");
}

std::pair<ChunkFrame, ChunkBlocks> ChunkPlacer::GetChunkAt(
	const Position origin,
	const size_t size,
	const std::shared_ptr<WorldGenerator> generator)
{
	const auto chunkFrame = ChunkFrame{origin, size};

	ChunkBlocks chunkBlocks;
	chunkBlocks.resize(size * size * size);
	
	generator->PaintChunk(chunkFrame, chunkBlocks);

	return std::pair<ChunkFrame, ChunkBlocks>(ChunkFrame{origin, size}, chunkBlocks);
}

void ChunkPlacer::UpdateLoadedChunksVector(std::vector<std::future<std::pair<ChunkFrame, ChunkBlocks>>>* futuresQueue, std::vector<std::pair<ChunkFrame, ChunkBlocks>>* chunksToBuildQueue)
{
	while(!futuresQueue->empty())
	{
		std::lock_guard<std::mutex> lock(BuildQueueMutex);

		for(auto currentFuture = futuresQueue->begin(); currentFuture != futuresQueue->end(); ++currentFuture)
		{
			if(currentFuture->_Is_ready())
			{
				const auto& chunkData = currentFuture->get();
				chunksToBuildQueue->push_back(chunkData);

				currentFuture = futuresQueue->erase(currentFuture);

				break;
			}
		}
	}
}

void ChunkPlacer::BuildChunksInQueue()
{
	const auto chunkData = _chunksToBeBuildQueue.back();
	_chunksToBeBuildQueue.pop_back();

	_loadedChunks[chunkData.first.origin] = std::make_unique<Chunk>(chunkData.first, chunkData.second, _generator->GetBlockMap());
}

void ChunkPlacer::AddNewChunks(const std::vector<Position>& currentChunksOrigins)
{
	const auto chunkSize = _order->GetChunkSize();

	for(const auto& origin : currentChunksOrigins)
	{
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			std::lock_guard<std::mutex> lock(BuildQueueMutex);
			_futures.push_back(std::async(std::launch::async, GetChunkAt, origin, chunkSize, _generator));
			_log.Trace("Added chunk: " + PositionToString(origin));
		}
	}

	_futuresPool.push_back(std::async(std::launch::async, UpdateLoadedChunksVector, &_futures, &_chunksToBeBuildQueue));

	_log.Debug("Finished adding new chunks!");
}


void ChunkPlacer::UpdateChunksAround(const Position& normalizedOrigin)
{
	const auto currentChunksAroundOrigins = _order->GetChunksAround(normalizedOrigin);

	RemoveStaleChunks(currentChunksAroundOrigins);
	AddNewChunks(currentChunksAroundOrigins);
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
	const auto currentNormalizedPosition = GetNormalizedPosition(position, _order->GetChunkSize());

	if (currentNormalizedPosition != _previousNormalizedPosition)
	{
		_previousNormalizedPosition = currentNormalizedPosition;
		UpdateChunksAround(currentNormalizedPosition);

		_log.Trace("Normalized position: " + PositionToString(currentNormalizedPosition));
	}
}

void ChunkPlacer::Bind(std::shared_ptr<WorldGenerator> generator)
{
	_generator = std::move(generator);
	UpdateChunksAround(_previousNormalizedPosition);
}

std::unordered_map<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks()
{
	if (!_chunksToBeBuildQueue.empty())
	{
		BuildChunksInQueue();
	}

	return _loadedChunks;
}
