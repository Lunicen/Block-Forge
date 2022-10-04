#pragma once
#include "Biomes/BiomePlacer.h"
#include "Chunks/Structure/ChunkBlocks.h"
#include "Chunks/Structure/ChunkFrame.h"

/// @class WorldGeneratorUtils
/// @brief Class that contains utilities that are useful for the @see WorldGenerator class.
class WorldGeneratorUtils
{
	static void OptimizeBlock(const Position& origin, BlockData& block, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);

public:

	/// @brief Optimizes the whole chunk.
	///	@details This method checks every block that is inside the chunk
	///	and modifies the block data for the optimal experience.
	/// @param frame - Frame of the chunk.
	///	@param blocks - The blocks inside the chunk.
	///	@param biomePlacer - The biome placer to extract the noise around the chunk.
	///	@attention Use this class **only** for chunks generated from noise.
	static void OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks, const BiomePlacer& biomePlacer);
};

