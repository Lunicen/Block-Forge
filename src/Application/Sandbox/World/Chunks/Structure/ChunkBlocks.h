#pragma once
#include "Application/Sandbox/Model/BlockModel.h"

/// @brief Contains the information about a certain block and the visibility of its faces.
struct BlockVisibility
{
	/// @brief A pointer to the model of a block.
	std::shared_ptr<BlockModel> model = nullptr;

	/// @brief Represents the visibility of block faces.
	///	@details This structure represents the visibility of block faces. 
	///	The value "true" means that the block face in a certain position should be visible.
	///	For instance, if the camera can see this block face, the value should remain true.
	///	Otherwise, if the block is hidden behind others and cannot be seen, the visibility of this face should be disabled.
	FacesVisibility visibility{true, true, true, true, true, true};
};

template <>
/// @brief A custom defined hash operator for the Position type variable.
///	@details This hash operator overload allows to use the 3d vector
///	as a key in the map.
struct std::hash<Position>
{
	/// @brief Definition of how to handle the passed origin as a key in the map.
    size_t operator()(const Position& origin) const noexcept
    {
        return std::hash<std::string>()
    	(
			std::to_string(origin.x) + "." +
			std::to_string(origin.y) + "." + 
			std::to_string(origin.z)
		);
    }
};

/// @class ChunkBlocks
/// @brief A structure that represents the body of typical chunk. Blocks and their visibility.
class ChunkBlocks
{
public:

	/// @brief The constructor.
	ChunkBlocks() = default;

	/// @brief Copy constructor.
	ChunkBlocks(const ChunkBlocks&) = default;

	/// @brief Move constructor.
	ChunkBlocks(ChunkBlocks&&) noexcept = default;
	
	/// @brief Copy assignment constructor.
	ChunkBlocks &operator=(const ChunkBlocks &) = default;

	/// @brief Move assignment constructor.
	ChunkBlocks &operator=(ChunkBlocks &&) noexcept = default;

	/// @brief Map with blocks that are placed inside the chunk.
	///	@details This map contains all blocks that are included in the chunk
	///	and maps the location of the block as a key, and it's model and
	///	faces visibility as a key.
	std::unordered_map<Position, BlockVisibility> block;

	~ChunkBlocks() = default;
};