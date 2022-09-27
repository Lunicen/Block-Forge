#include "ChunkPlacer.h"

#include "Application/Sandbox/World/Biomes/Biome.h"

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
}

void ChunkPlacer::AddNewChunks(const std::vector<Position>& currentChunksOrigins)
{
	for (const auto& origin : currentChunksOrigins)
	{
		if (_loadedChunks.find(origin) == _loadedChunks.end())
		{
			_log.Trace("Added chunk: " + PositionToString(origin));
			_loadedChunks[origin] = std::move(_chunkBuilder.Build(origin, _order->GetChunkSize(), *_generator));
		}
	}
}

void ChunkPlacer::UpdateChunksAround(const Position& normalizedOrigin)
{
	const auto currentChunksAroundOrigins = _order->GetChunksAround(normalizedOrigin);

	RemoveStaleChunks(currentChunksAroundOrigins);
	AddNewChunks(currentChunksAroundOrigins);
}

ChunkPlacer::ChunkPlacer(const OrderType orderType, const size_t chunkSize, const size_t renderDistance, const Position& initPosition)
{
	_previousNormalizedPosition = GetNormalizedPosition(initPosition, chunkSize);

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
}

std::unordered_map<Position, std::unique_ptr<Chunk>>& ChunkPlacer::GetChunks()
{
	return _loadedChunks;
}
