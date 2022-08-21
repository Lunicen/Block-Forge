#include "ChunkUtils.h"

float ChunkUtils::CalculateMidPoint(const int chunkSize)
{
	auto result = static_cast<float>(chunkSize) / 2.0f;
	if (chunkSize % 2 == 0)
	{
		result += 0.5f;
	}

	return result;
}

ChunkData ChunkUtils::InitializeData(const int chunkSize)
{
	ChunkData chunk;

	// TODO - HERE IS THE CRASH
	chunk.blocks.resize(chunkSize, std::vector<std::vector<std::unique_ptr<Block>>>());
	chunk.visibilityFlag.resize(chunkSize);
	for (auto x = 0; x < chunkSize; ++x)
	{
		chunk.blocks[x].resize(chunkSize, std::vector<std::unique_ptr<Block>>());
		chunk.visibilityFlag[x].resize(chunkSize);
		for (auto y = 0; y < chunkSize; ++y)
		{
			chunk.blocks[x][y].resize(chunkSize, std::unique_ptr<Block>());
			chunk.visibilityFlag[x][y].resize(chunkSize);
		}
	}

	return chunk;
}
