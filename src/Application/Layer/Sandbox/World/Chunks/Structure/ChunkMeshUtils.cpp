#include "ChunkMeshUtils.h"

#include "Application/Layer/Sandbox/World/Chunks/ChunkUtils.h"

void ChunkMeshUtils::AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices,
	const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh)
{
	constexpr auto quadVerticesCount = 4;
	for (auto i = 0; i < quadVerticesCount; ++i)
	{
		mesh.emplace_back(Vertex{faceVertices[i] + Point3D(origin), faceTextureCoordinates[i]});
	}
}

std::vector<Vertex> ChunkMeshUtils::GetMeshVertices(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap)
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
		auto faceVertices = blockMap.GetFaceVertices();

		if (blockFlags & BlockFlag.frontFace)	AddFaceToMesh(origin, faceVertices.front, faceModels.front.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.backFace)	AddFaceToMesh(origin, faceVertices.back, faceModels.back.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.leftFace)	AddFaceToMesh(origin, faceVertices.left, faceModels.left.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.rightFace)	AddFaceToMesh(origin, faceVertices.right, faceModels.right.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.topFace)		AddFaceToMesh(origin, faceVertices.top, faceModels.top.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.bottomFace)	AddFaceToMesh(origin, faceVertices.bottom, faceModels.bottom.GetUvCoordinates(), vertices);
	}

	return vertices;
}
