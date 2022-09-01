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

ChunkBlocks ChunkUtils::InitializeData(const int size)
{
	ChunkBlocks chunk;

	InitializeVector3D(chunk.blocks, size);
	InitializeVector3D(chunk.isBlockVisibleAt, size);

	return chunk;
}