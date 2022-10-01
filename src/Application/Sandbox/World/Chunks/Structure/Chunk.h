#pragma once
#include "Application/Sandbox/Camera.h"
#include "ChunkBlocks.h"
#include "ChunkMesh.h"
#include "Application/Sandbox/Model/Mesh/DynamicMesh.h"

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk at the certain position.
class Chunk
{
	ChunkMesh _mesh;
	std::shared_ptr<Texture> _blockTexture;
	ChunkBlocks _blocks;

public:

	/// @brief The constructor.
	///	@param size - Size of the chunk edge.
	///	@param blocksTexture - Texture atlas of the blocks inside the chunk.
	///	@param shader - Reference to the blocks shader.
	explicit Chunk(const size_t& size, std::shared_ptr<Texture> blocksTexture, Shader& shader);

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param blocks - The blocks inside the chunk.
	///	@param blocksTexture - Texture atlas of the blocks inside the chunk.
	///	@param size - Size of the chunks edge.
	///	@param shader - Reference to the blocks shader.
	explicit Chunk(ChunkBlocks blocks, std::shared_ptr<Texture> blocksTexture, const size_t& size, Shader& shader);

	/// @brief Draws the chunk in the world.
	///	@param camera - reference to the camera so that the blocks could be seen.
	void Draw(const Camera& camera) const;
};

