#include "application/layer/sandbox/world/chunks/structure/chunk_mesh.h"
#include "application/layer/sandbox/world/chunks/structure/chunk_mesh_utils.h"

ChunkMesh::ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk)
	: _mesh(std::vector<Vertex>(), _indicesPattern, blockShader, sizeOfChunk * sizeOfChunk * sizeOfChunk)
{
}

ChunkMesh::ChunkMesh(const std::vector<Vertex>& vertices, Shader& blockShader, const size_t& sizeOfChunk)
	: _mesh(vertices, _indicesPattern, blockShader, sizeOfChunk * sizeOfChunk * sizeOfChunk)
{
}

void ChunkMesh::Rebuild(const std::vector<Vertex>& vertices)
{
	_mesh.Update(vertices);
}

void ChunkMesh::Rebuild(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap)
{
	_mesh.Update(ChunkMeshUtils::GetMeshVertices(frame, blocks, blockMap));
}

void ChunkMesh::Draw(const Texture& blocksTexture, const Camera& camera)
{
	_mesh.Draw(blocksTexture, camera);
}
