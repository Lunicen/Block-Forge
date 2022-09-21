#pragma once
#include "Structure/ChunkBlocks.h"

/// @class ChunkUtils
/// @brief Set of functions that could be used in other classes.
class ChunkUtils
{
public:
	/// @brief Creates 3d vector with a size of a chunk.
	///	@param vector - vector to initialize.
	///	@param size - size of the chunk.
	template <class Value>
	static void InitializeVector3D(std::vector<std::vector<std::vector<Value>>>& vector, const size_t& size);
};

template <class Value>
void ChunkUtils::InitializeVector3D(std::vector<std::vector<std::vector<Value>>>& vector, const size_t& size)
{
	vector.resize(size);
	for (size_t x = 0; x < size; ++x)
	{
		vector[x].resize(size);
		for (size_t y = 0; y < size; ++y)
		{
			vector[x][y].resize(size);
		}
	}
}
