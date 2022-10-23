#include "ChunkMesh.h"

#include "ChunkMeshUtils.h"

ChunkMesh::ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk)
{
	const std::vector<TriangleIndexes> indicesPattern =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	const auto maxInstancesAmount = sizeOfChunk * sizeOfChunk * sizeOfChunk;

	_mesh = std::make_unique<DynamicMesh>(std::vector<Vertex>(), indicesPattern, blockShader, maxInstancesAmount);
}

ChunkMesh::ChunkMesh(const std::vector<Vertex>& vertices, Shader& blockShader, const size_t& sizeOfChunk)
{
	const std::vector<TriangleIndexes> indicesPattern =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	const auto maxInstancesAmount = sizeOfChunk * sizeOfChunk * sizeOfChunk;

	_mesh = std::make_unique<DynamicMesh>(vertices, indicesPattern, blockShader, maxInstancesAmount);
}

void ChunkMesh::Set(const std::vector<Vertex>& vertices) const
{
	_mesh->Update(vertices);
}

void ChunkMesh::Rebuild(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap) const
{
	_mesh->Update(ChunkMeshUtils::GetMeshVertices(frame, blocks, blockMap));
}

void ChunkMesh::Draw(const Texture& blocksTexture, const Camera& camera) const
{
	_mesh->Draw(blocksTexture, camera);
}
