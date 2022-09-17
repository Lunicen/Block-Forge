#pragma once
#include "Sandbox/World/Blocks/BlockRenderer.h"

/// @class ChunkBlocks
/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
class ChunkBlocks
{
public:

	/// @brief Map with blocks that are placed inside the chunk.
	///	@details This map contains all blocks that are included in the chunk
	///	and maps the location of the block as a key, and it's model and
	///	faces visibility as a key.
	std::unordered_map<glm::ivec3, BlockVisibility> block;
};
