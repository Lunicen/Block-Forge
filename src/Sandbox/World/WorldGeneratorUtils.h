#pragma once
#include "Biomes/BiomePlacer.h"
#include "Chunks/Structure/ChunkBlocks.h"
#include "Chunks/Structure/ChunkFrame.h"

class WorldGeneratorUtils
{
	static void OptimizeBlock(const Position& origin, BlockVisibility& block, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);

public:
	static void OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks, const BiomePlacer& biomePlacer);
};

