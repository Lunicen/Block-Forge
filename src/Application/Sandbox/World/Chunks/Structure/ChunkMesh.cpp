#include "ChunkMesh.h"

void ChunkMesh::AddFaceToMesh(
	const std::array<Point3D, 4>& faceVertices,
	const std::array<Point, 4>& faceTextureCoordinates,
	std::vector<Vertex>& mesh)
{
	constexpr auto quadVerticesCount = 4;
	for (auto i = 0; i < quadVerticesCount; ++i)
	{
		mesh.emplace_back(Vertex{faceVertices[i], faceTextureCoordinates[i]});
	}
}

ChunkMesh::ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk) : _blockShader(blockShader)
{
	const std::vector<TriangleIndexes> indicesPattern =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	const auto maxInstancesAmount = sizeOfChunk * sizeOfChunk * sizeOfChunk;

	_mesh = std::make_unique<DynamicMesh>(std::vector<Vertex>(), indicesPattern, _blockShader, maxInstancesAmount);
}

void ChunkMesh::Rebuild(const ChunkBlocks& blocks) const
{
	std::vector<Vertex> vertices;

	for (const auto& block : blocks)
	{
		auto& faceModels = block.second.model->GetFaces();
		const auto& facesVisibility = block.second.visibility;

		if (facesVisibility.front)	AddFaceToMesh(_faceVertices.front, faceModels.front.GetUvCoordinates(), vertices);
		if (facesVisibility.back)	AddFaceToMesh(_faceVertices.back, faceModels.back.GetUvCoordinates(), vertices);
		if (facesVisibility.left)	AddFaceToMesh(_faceVertices.left, faceModels.left.GetUvCoordinates(), vertices);
		if (facesVisibility.right)	AddFaceToMesh(_faceVertices.right, faceModels.right.GetUvCoordinates(), vertices);
		if (facesVisibility.top)	AddFaceToMesh(_faceVertices.top, faceModels.top.GetUvCoordinates(), vertices);
		if (facesVisibility.bottom)	AddFaceToMesh(_faceVertices.bottom, faceModels.bottom.GetUvCoordinates(), vertices);
	}

	_mesh->Update(vertices);
}

void ChunkMesh::Draw(const Texture& blocksTexture, const Camera& camera) const
{
	_mesh->Draw(blocksTexture, camera);
}
