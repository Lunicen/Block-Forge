#pragma once
#include <vector>

#include "ChunkBlocks.h"
#include "ChunkFrame.h"
#include "Application/Layer/Sandbox/Model/Mesh/Geometry/Structures.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"

class ChunkMeshUtils
{
	static void AddFaceToMesh(const Position& origin, const std::array<Point3D, 4>& faceVertices, const std::array<Point, 4>& faceTextureCoordinates, std::vector<Vertex>& mesh);

public:
	static std::vector<Vertex> GetMeshVertices(const ChunkFrame& frame, const ChunkBlocks& blocks, BlockMap& blockMap);
};

