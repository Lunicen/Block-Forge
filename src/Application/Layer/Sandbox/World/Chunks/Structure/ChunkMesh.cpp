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
		if (blocks[i] == nullptr)
		{
			continue;
		}

		struct FaceVertices
		{
			std::array<Point3D, 4> front
			{
				{
					Point3D{0.0f, 0.0f, 0.0f},
					Point3D{1.0f, 0.0f, 0.0f},
					Point3D{1.0f, 1.0f, 0.0f},
					Point3D{0.0f, 1.0f, 0.0f}
				}
			};

			std::array<Point3D, 4> back
			{
				{
					Point3D{0.0f, 0.0f, 1.0f},
					Point3D{0.0f, 1.0f, 1.0f},
					Point3D{1.0f, 1.0f, 1.0f},
					Point3D{1.0f, 0.0f, 1.0f}
				}
			};

			std::array<Point3D, 4> left
			{
				{
					Point3D{0.0f, 0.0f, 0.0f},
					Point3D{0.0f, 1.0f, 0.0f},
					Point3D{0.0f, 1.0f, 1.0f},
					Point3D{0.0f, 0.0f, 1.0f}
				}
			};

			std::array<Point3D, 4> right
			{
				{
					Point3D{1.0f, 0.0f, 0.0f},
					Point3D{1.0f, 0.0f, 1.0f},
					Point3D{1.0f, 1.0f, 1.0f},
					Point3D{1.0f, 1.0f, 0.0f}
				}
			};

			std::array<Point3D, 4> top
			{
				{
					Point3D{0.0f, 1.0f, 0.0f},
					Point3D{1.0f, 1.0f, 0.0f},
					Point3D{1.0f, 1.0f, 1.0f},
					Point3D{0.0f, 1.0f, 1.0f}
				}
			};

			std::array<Point3D, 4> bottom
			{
				{
					Point3D{0.0f, 0.0f, 0.0f},
					Point3D{0.0f, 0.0f, 1.0f},
					Point3D{1.0f, 0.0f, 1.0f},
					Point3D{1.0f, 0.0f, 0.0f},
				}
			};
		} faceVertices;

		auto origin = ChunkUtils::GetBlockPosition(i, frame.size) + frame.origin * static_cast<int>(frame.size);
		auto faceModels = blockMap[blocks[i]->blockModel]->GetFaces();
		const auto& blockFlags = blocks[i]->blockFlags;

		if (blockFlags & 0b10000000)	AddFaceToMesh(origin, faceVertices.front, faceModels.front.GetUvCoordinates(), vertices);
		if (blockFlags & 0b01000000)	AddFaceToMesh(origin, faceVertices.back, faceModels.back.GetUvCoordinates(), vertices);
		if (blockFlags & 0b00100000)	AddFaceToMesh(origin, faceVertices.left, faceModels.left.GetUvCoordinates(), vertices);
		if (blockFlags & 0b00010000)	AddFaceToMesh(origin, faceVertices.right, faceModels.right.GetUvCoordinates(), vertices);
		if (blockFlags & 0b00001000)	AddFaceToMesh(origin, faceVertices.top, faceModels.top.GetUvCoordinates(), vertices);
		if (blockFlags & 0b00000100)	AddFaceToMesh(origin, faceVertices.bottom, faceModels.bottom.GetUvCoordinates(), vertices);
	}

	_mesh->Update(vertices);
}

void ChunkMesh::Draw(const Texture& blocksTexture, const Camera& camera) const
{
	_mesh->Draw(blocksTexture, camera);
}
