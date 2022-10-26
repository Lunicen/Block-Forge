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

	explicit Chunk(size_t chunkSize, BlockMap& blockMap);

	void Load(const ChunkBlocks& blocks, const std::vector<Vertex>& precalculatedMesh);
	void Load(const ChunkBlocks& blocks, ChunkFrame frame, BlockMap& blockMap);

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param frame - Frame of the chunk.
	///	@param blocks - The blocks inside the chunk.
	///	@param blockMap - Reference to the blocks map.
	explicit Chunk(ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap);

	explicit Chunk(ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap, const std::vector<Vertex>&
	               precalculatedMesh);

	/// @brief Draws the chunk in the world.
	///	@param blockTexture - Reference texture atlas that the blocks are using.
	///	@param camera - Reference to the camera so that the blocks could be seen.
	void Draw(const TextureAtlas& blockTexture, const Camera& camera);
};

