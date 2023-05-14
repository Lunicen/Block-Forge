#pragma once
#include <vector>

#include "ChunkBlocks.h"
#include "ChunkFrame.h"
#include "Application/Layer/Sandbox/Model/Mesh/Geometry/Structures.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

/// @class ChunkMeshUtils
///	@brief A simple utility class made for chunk calculations.
class ChunkMeshUtils
{
	static void AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:

	/// @brief Calculates mesh vertices based on its blocks data.
	///	@param frame - Frame of the chunk.
	///	@param blocks - The blocks inside the chunk.
	///	@param blockMap - Reference to the blocks map.
	static std::vector<Vertex> GetMeshVertices(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap);
};

