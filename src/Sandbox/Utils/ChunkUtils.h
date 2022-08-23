#pragma once
#include "Sandbox/World/ChunkData.h"

/// @class ChunkUtils
/// @brief Set of functions that could be used in other classes.
class ChunkUtils
{
public:

	/// @brief Calculated the midpoint of the chunk.
	///	@param size - size of the chunk.
	static float CalculateMidPoint(int size);

	/// @brief Initializes chunk data.
	///	@param size - size of the chunk.
	static ChunkData InitializeData(int size);
};