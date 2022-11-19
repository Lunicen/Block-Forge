#pragma once
#include "Application/Layer/Sandbox/Model/Mesh/Geometry/Structures.h"

/// @class ChunkUtils
///	@brief The utility class that provides an easy ways for performing
///	calculations related to the chunks.
class ChunkUtils
{
public:

	/// @brief Returns the block index from the flattened 3d chunk array.
	///	@param origin - position of the block relative to the chunk origin.
	///	@param chunkSize - size of the chunk (in one dimension).
	static size_t GetBlockIndex(const Position& origin, const size_t& chunkSize)
	{
		const auto& x = origin.x;
		const auto& y = origin.y;
		const auto& z = origin.z;

		return x + chunkSize * (y + chunkSize * z);
	}

	/// @brief Returns the block position based on its index from the flattened 3d array.
	///	@param blockIndex - the array index.
	///	@param chunkSize - size of the chunk (in one dimension).
	static Position GetBlockPosition(size_t blockIndex, const size_t& chunkSize)
	{
		const auto z = blockIndex / (chunkSize * chunkSize);

		blockIndex -= z * chunkSize * chunkSize;
		const auto y = blockIndex / chunkSize;
		const auto x = blockIndex % chunkSize;

		return {x, y, z};
	}

	static Position GetNormalizedPosition(const Point3D& position, const size_t& chunkSize)
	{
		auto normalizedPosition = position;

		normalizedPosition /= chunkSize;

		normalizedPosition.x = floor(normalizedPosition.x);
		normalizedPosition.y = floor(normalizedPosition.y);
		normalizedPosition.z = floor(normalizedPosition.z);

		return { normalizedPosition };
	}
};
