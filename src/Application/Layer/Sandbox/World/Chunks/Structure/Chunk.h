#pragma once
#include "ChunkBlocks.h"
#include "ChunkMesh.h"
//#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"
//#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk at the certain position.
class Chunk
{
	ChunkMesh _mesh;
	ChunkBlocks _blocks;

public:

	/// @brief The constructor.
	///	@param chunkSize - the size of the chunk.
	///	@param blockMap - Reference to the blocks map.
	explicit Chunk(size_t chunkSize, BlockMap& blockMap);

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param frame - Frame of the chunk.
	///	@param blocks - The blocks inside the chunk.
	///	@param blockMap - Reference to the blocks map.
	explicit Chunk(ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap);

	/// @brief Loads blocks data that are inside the chunk
	///	@note This data is required for chunk modifying.
	///	@param blocks - chunk blocks.
	void LoadBlocks(const ChunkBlocks& blocks);

	ChunkBlocks GetBlocks();

	/// @brief Loads precalculated mesh.
	///	@param precalculatedMesh - precalculated mesh.
	void LoadMesh(const std::vector<Vertex>& precalculatedMesh);

	void LoadBlocksAndBuildMesh(const ChunkBlocks& blocks, const ChunkFrame& frame, BlockMap& blockMap);

	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param frame - Frame of the chunk.
	///	@param blocks - The blocks inside the chunk.
	///	@param blockMap - Reference to the blocks map.
	/// @param precalculatedMesh - vertices of precalculated chunk mesh.
	explicit Chunk(ChunkFrame frame, ChunkBlocks blocks, BlockMap& blockMap, const std::vector<Vertex>&
	               precalculatedMesh);

	/// @brief Draws the chunk in the world.
	///	@param blockTexture - Reference texture atlas that the blocks are using.
	///	@param camera - Reference to the camera so that the blocks could be seen.
	void Draw(const TextureAtlas& blockTexture, const Camera& camera);
};

