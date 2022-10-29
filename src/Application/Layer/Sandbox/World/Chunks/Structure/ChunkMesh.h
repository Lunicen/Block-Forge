#pragma once
#include "ChunkBlocks.h"
#include "ChunkFrame.h"
#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class ChunkMesh
///	@brief Represents the chunk mesh and manages it in a runtime.
class ChunkMesh
{
	const std::vector<TriangleIndexes> _indicesPattern =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};

	DynamicMesh _mesh;

public:

	/// @brief The constructor.
	///	@param blockShader - Shader of the blocks inside the chunk.
	///	@param sizeOfChunk - Size of the chunk edge.
	explicit ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk);

	/// @brief The constructor.
	/// @param vertices - vertices of precalculated chunk mesh.
	///	@param blockShader - Shader of the blocks inside the chunk.
	///	@param sizeOfChunk - Size of the chunk edge.
	explicit ChunkMesh(const std::vector<Vertex>& vertices, Shader& blockShader, const size_t& sizeOfChunk);

	/// @brief Rebuilds the mesh basing on the precalculated mesh.
	/// @param vertices - vertices of precalculated chunk mesh.
	void Rebuild(const std::vector<Vertex>& vertices);

	/// @brief Rebuilds the mesh basing on the passed blocks.
	///	@param frame - Frame of the chunk.
	///	@param blocks - Blocks inside the chunk.
	///	@param blockMap - Reference to the block map.
	void Rebuild(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap);

	/// @brief Renders blocks inside the chunk.
	///	@param blocksTexture - The texture that the blocks are using.
	///	@param camera - Reference to the camera, so the blocks could be seen.
	void Draw(const Texture& blocksTexture, const Camera& camera);
};

