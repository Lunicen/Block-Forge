#pragma once
#include "Application/Layer/Sandbox/Model/Mesh/Geometry/Structures.h"

class ChunkUtils
{
public:
	static size_t GetBlockIndex(const Position& origin, const size_t& chunkSize)
	{
		const auto& x = origin.x;
		const auto& y = origin.y;
		const auto& z = origin.z;

		return x + chunkSize * (y + chunkSize * z);
	}

	static Position GetBlockPosition(size_t blockIndex, const size_t& chunkSize)
	{
		const auto z = blockIndex / (chunkSize * chunkSize);

		blockIndex -= z * chunkSize * chunkSize;
		const auto y = blockIndex / chunkSize;
		const auto x = blockIndex % chunkSize;

		return {x, y, z};
	}
};
