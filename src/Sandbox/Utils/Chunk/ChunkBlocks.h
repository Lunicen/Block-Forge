#pragma once
#include <vector>

#include "Sandbox/Block.h"

/// @class ChunkBlocks
/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
class ChunkBlocks
{
public:

	/// @brief Vector of the visibility of the blocks.
	///	@note Made for optimization purposes.
	std::vector<std::vector<std::vector<bool>>> isBlockVisibleAt = {{}};

	/// @brief The actual structure of the chunk - blocks placement.
	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> blocks;
};
