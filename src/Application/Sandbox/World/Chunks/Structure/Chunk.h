#pragma once
#include "Application/Sandbox/Camera.h"
#include "ChunkBlocks.h"

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk at the certain position.
class Chunk
{
	ChunkBlocks _blocks;

public:
	Chunk() = default;

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param blocks - the blocks inside the chunk.
	///	@attention Do **NOT** give the exact origin position, where You want to have a chunk placed.
	///	In the constructor it's implemented to place them respectively to the chunk size.
	///	If the defined chunk size is 16 and the origin is (1, 1, 1) the real chunk origin will be (16, 16, 16).
	explicit Chunk(ChunkBlocks blocks);

	/// @brief Draws the chunk in the world.
	///	@param camera - reference to the camera so that the blocks could be seen.
	void Draw(const Camera& camera) const;
};

