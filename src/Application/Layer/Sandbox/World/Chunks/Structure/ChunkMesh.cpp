#include "ChunkMesh.h"

#include "Application/Layer/Sandbox/World/Chunks/ChunkUtils.h"

void ChunkMesh::AddFaceToMesh(
	const Position& origin,
	const std::array<Point3D, 4>& faceVertices,
	const std::array<Point, 4>& faceTextureCoordinates,
	std::vector<Vertex>& mesh)
{
	constexpr auto quadVerticesCount = 4;
	for (auto i = 0; i < quadVerticesCount; ++i)
	{
		mesh.emplace_back(Vertex{faceVertices[i] + Point3D(origin), faceTextureCoordinates[i]});
	}
}

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

void ChunkMesh::Rebuild(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap) const
{
	std::vector<Vertex> vertices;

	for (size_t i = 0; i < blocks.size(); ++i)
	{
		const auto& blockFlags = blocks[i].blockFlags;

		// If block is disabled
		if ((blockFlags & BlockFlag.activate) == 0)
		{
			continue;
		}

		auto origin = ChunkUtils::GetBlockPosition(i, frame.size) + frame.origin * static_cast<int>(frame.size);
		auto faceModels = blockMap[blocks[i].blockModel]->GetFaces();

		if (blockFlags & BlockFlag.frontFace)	AddFaceToMesh(origin, _faceVertices.front, faceModels.front.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.backFace)	AddFaceToMesh(origin, _faceVertices.back, faceModels.back.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.leftFace)	AddFaceToMesh(origin, _faceVertices.left, faceModels.left.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.rightFace)	AddFaceToMesh(origin, _faceVertices.right, faceModels.right.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.topFace)		AddFaceToMesh(origin, _faceVertices.top, faceModels.top.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.bottomFace)	AddFaceToMesh(origin, _faceVertices.bottom, faceModels.bottom.GetUvCoordinates(), vertices);
	}

	_mesh->Update(vertices);
}

void ChunkMesh::Draw(const Texture& blocksTexture, const Camera& camera) const
{
	_mesh->Draw(blocksTexture, camera);
}
