#pragma once
#include <vector>

#include "Sandbox/Block.h"

/// @class ChunkData
/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
class ChunkData
{
public:

	/// @brief Vector of the visibility of the blocks.
	///	@note Made for optimization purposes.
	std::vector<std::vector<std::vector<bool>>> isBlockVisibleAt = {{}};

	/// @brief The actual structure of the chunk - blocks placement.
	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> blocks;
};
