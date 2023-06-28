#pragma once
#include <vector>

#include "application/layer/sandbox/world/chunks/structure/chunk_blocks.h"
#include "application/layer/sandbox/world/chunks/structure/chunk_frame.h"
#include "application/layer/sandbox/model/mesh/geometry/structures.h"
#include "application/layer/sandbox/world/blocks/block_map.h"

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

