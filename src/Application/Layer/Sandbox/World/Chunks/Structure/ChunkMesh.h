#pragma once
#include "ChunkBlocks.h"
#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"

/// @class ChunkMesh
///	@brief Represents the chunk mesh and manages it in a runtime.
class ChunkMesh
{
	std::unique_ptr<DynamicMesh> _mesh = nullptr;
	Shader& _blockShader;

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
	};
	const FaceVertices _faceVertices;

	static void AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:

	/// @brief The constructor.
	///	@param blockShader - Shader of the blocks inside the chunk.
	///	@param sizeOfChunk - Size of the chunk edge.
	explicit ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk);

	/// @brief Rebuilds the mesh basing on the passed blocks.
	///	@param blocks - Blocks inside the chunk.
	void Rebuild(const ChunkBlocks& blocks) const;

	/// @brief Renders blocks inside the chunk.
	///	@param blocksTexture - The texture that blocks uses.
	///	@param camera - Reference to the camera, so the blocks could be seen.
	void Draw(const Texture& blocksTexture, const Camera& camera) const;
};

