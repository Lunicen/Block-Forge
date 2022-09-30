#pragma once
#include "ChunkBlocks.h"
#include "Application/Sandbox/Model/Mesh/DynamicMesh.h"

class ChunkMesh
{
	std::unique_ptr<DynamicMesh> _mesh = nullptr;
	Shader& _blockShader;

	const struct FaceVertices
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
				Point3D{0.0f, 1.0f, 0.0f},
				Point3D{1.0f, 1.0f, 0.0f},
				Point3D{1.0f, 1.0f, 1.0f},
				Point3D{0.0f, 1.0f, 1.0f}
			}
		};

		std::array<Point3D, 4> top
		{
			{
				Point3D{0.0f, 0.0f, 1.0f},
				Point3D{0.0f, 1.0f, 1.0f},
				Point3D{1.0f, 1.0f, 1.0f},
				Point3D{1.0f, 0.0f, 1.0f}
			}
		};

		std::array<Point3D, 4> bottom
		{
			{
				Point3D{0.0f, 0.0f, 1.0f},
				Point3D{0.0f, 1.0f, 1.0f},
				Point3D{1.0f, 1.0f, 1.0f},
				Point3D{1.0f, 0.0f, 1.0f}
			}
		};
		
	} _faceVertices;

	static void AddFaceToMesh(const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:
	explicit ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk);

	void Rebuild(const ChunkBlocks& blocks) const;

	void Draw(const Texture& blocksTexture, const Camera& camera) const;
};

