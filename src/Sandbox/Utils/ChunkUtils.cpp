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
