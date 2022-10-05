#pragma once
#include "ChunkBlocks.h"
#include "ChunkFrame.h"
#include "Application/Layer/Sandbox/Model/Mesh/DynamicMesh.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class ChunkMesh
///	@brief Represents the chunk mesh and manages it in a runtime.
class ChunkMesh
{
	std::unique_ptr<DynamicMesh> _mesh = nullptr;

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
	FaceVertices _faceVertices;

	static void AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:

	/// @brief The constructor.
	///	@param blockShader - Shader of the blocks inside the chunk.
	///	@param sizeOfChunk - Size of the chunk edge.
	explicit ChunkMesh(Shader& blockShader, const size_t& sizeOfChunk);

	/// @brief Rebuilds the mesh basing on the passed blocks.
	///	@param frame - Frame of the chunk.
	///	@param blocks - Blocks inside the chunk.
	///	@param blockMap - Reference to the block map.
	void Rebuild(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap) const;

	/// @brief Renders blocks inside the chunk.
	///	@param blocksTexture - The texture that the blocks are using.
	///	@param camera - Reference to the camera, so the blocks could be seen.
	void Draw(const Texture& blocksTexture, const Camera& camera) const;
};

