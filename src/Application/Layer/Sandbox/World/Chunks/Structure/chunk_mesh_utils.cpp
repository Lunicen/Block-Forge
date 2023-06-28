#include "application/layer/sandbox/world/chunks/structure/chunk_mesh_utils.h"
#include "application/layer/sandbox/world/chunks/chunk_utils.h"

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
		auto [frontModel, backModel, leftModel, rightModel, topModel, bottomModel] = blockMap[blocks[i].blockModel]->GetFaces();
		auto [frontFace, backFace, leftFace, rightFace, topFace, bottomFace] = blockMap.GetFaceVertices();

		if (blockFlags & BlockFlag.frontFace)	AddFaceToMesh(origin, frontFace,  frontModel.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.backFace)	AddFaceToMesh(origin, backFace,   backModel.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.leftFace)	AddFaceToMesh(origin, leftFace,   leftModel.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.rightFace)	AddFaceToMesh(origin, rightFace,  rightModel.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.topFace)		AddFaceToMesh(origin, topFace,	  topModel.GetUvCoordinates(), vertices);
		if (blockFlags & BlockFlag.bottomFace)	AddFaceToMesh(origin, bottomFace, bottomModel.GetUvCoordinates(), vertices);
	}

	return vertices;
}
