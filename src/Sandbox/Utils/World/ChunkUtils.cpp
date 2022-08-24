#include "ChunkUtils.h"

float ChunkUtils::CalculateMidPoint(const int size)
{
	auto result = static_cast<float>(size) / 2.0f;
	if (size % 2 == 0)
	{
		result += 0.5f;
	}

	return result;
}

ChunkData ChunkUtils::InitializeData(const int size)
{
	ChunkData chunk;
	
	chunk.blocks.resize(size);
	chunk.isBlockVisibleAt.resize(size);
	for (auto x = 0; x < size; ++x)
	{
		chunk.blocks[x].resize(size);
		chunk.isBlockVisibleAt[x].resize(size);
		for (auto y = 0; y < size; ++y)
		{
			chunk.blocks[x][y].resize(size);
			chunk.isBlockVisibleAt[x][y].resize(size);
		}
	}

	return chunk;
}
