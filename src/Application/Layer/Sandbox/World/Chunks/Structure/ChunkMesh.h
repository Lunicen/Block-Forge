#pragma once
#include "ChunkBlocks.h"
#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class ChunkMesh
///	@brief Represents the chunk mesh and manages it in a runtime.
class ChunkMesh
{
	std::unique_ptr<DynamicMesh> _mesh = nullptr;

	static void AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:

	/// @brief The constructor.
	///	@param blockShader - Shader of the blocks inside the chunk.
	///	@param sizeOfChunk - Size of the chunk edge.
	explicit ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk);

	/// @brief Rebuilds the mesh basing on the passed blocks.
	///	@param blocks - Blocks inside the chunk.
	void Rebuild(const ChunkBlocks& blocks, BlockMap& blockMap) const;

	/// @brief Renders blocks inside the chunk.
	///	@param blocksTexture - The texture that blocks uses.
	///	@param camera - Reference to the camera, so the blocks could be seen.
	void Draw(const Texture& blocksTexture, const Camera& camera) const;
};

