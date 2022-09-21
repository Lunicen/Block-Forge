#pragma once
#include "Sandbox/Model/BlockModel.h"

struct BlockVisibility
{
	std::shared_ptr<BlockModel> model = nullptr;
	FacesVisibility visibility{true, true, true, true, true, true};

	BlockVisibility() = default;

	BlockVisibility(const BlockVisibility&) = default;
	BlockVisibility(BlockVisibility&&) = default;

	BlockVisibility& operator=(const BlockVisibility&) = default;
	BlockVisibility& operator=(BlockVisibility&&) = default;

	~BlockVisibility() = default;
};

template <>
struct std::hash<Position>
{
    size_t operator()(const Position &origin) const noexcept
    {
        return std::hash<std::string>()
    	(
			std::to_string(origin.x) + 
			std::to_string(origin.y) + 
			std::to_string(origin.z)
		);
    }
};

/// @class ChunkBlocks
/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
class ChunkBlocks
{
public:

	/// @brief Map with blocks that are placed inside the chunk.
	///	@details This map contains all blocks that are included in the chunk
	///	and maps the location of the block as a key, and it's model and
	///	faces visibility as a key.
	std::unordered_map<Position, BlockVisibility> block;
};
