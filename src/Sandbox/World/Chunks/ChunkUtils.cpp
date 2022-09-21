#include "ChunkUtils.h"

float ChunkUtils::CalculateMidPoint(const size_t& size)
{
	auto result = static_cast<float>(size) / 2.0f;
	if (size % 2 == 0)
	{
		result += 0.5f;
	}

	return result;
}