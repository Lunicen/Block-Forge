#pragma once
#include "Application/Layer/Sandbox/Camera.h"
#include "ChunkBlocks.h"
#include "ChunkMesh.h"
#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk at the certain position.
class Chunk
{
	ChunkMesh _mesh;
	ChunkBlocks _blocks;

public:

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param blocks - The blocks inside the chunk.
	///	@param blocksTexture - Texture atlas of the blocks inside the chunk.
	///	@param size - Size of the chunks edge.
	///	@param shader - Reference to the blocks shader.
	explicit Chunk(ChunkBlocks blocks, BlockMap& blockMap, const size_t& size);

	/// @brief Draws the chunk in the world.
	///	@param camera - reference to the camera so that the blocks could be seen.
	void Draw(const TextureAtlas& blockTexture, const Camera& camera) const;
};

