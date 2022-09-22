#pragma once
#include <glm/vec3.hpp>

#include "Sandbox/Camera.h"
#include "ChunkFrame.h"
#include "ChunkBlocks.h"

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk at the certain position.
class Chunk
{
	ChunkFrame _frame;
	ChunkBlocks _blocks;
	Camera& _camera;

public:
	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param frame - the frame of the chunk.
	///	@param blocks - the blocks inside the chunk.
	///	@param camera - reference to the camera so that the blocks could be seen.
	///	@attention Do **NOT** give the exact origin position You want to have a chunk placed.
	///	In the constructor it's implemented to place them respectively to the chunk size.
	///	If the defined chunk size is 16 and the origin is (1, 1, 1) the real chunk origin will be (16, 16, 16).
	explicit Chunk(const ChunkFrame& frame, ChunkBlocks blocks, Camera& camera);

	/// @brief Draws the chunk in the world.
	void Draw() const;

	/// @brief Get the **actual** origin of the chunk.
	glm::ivec3 GetOrigin() const;
};

