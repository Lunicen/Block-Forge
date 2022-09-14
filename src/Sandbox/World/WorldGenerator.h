#pragma once
#include "Biomes/BiomePlacer.h"
#include "Biomes/BiomeProvider.h"

/// @class WorldGenerator
/// @brief Handles generating the world.
///	@details This class is made for transforming chunks according to the biomes that are specified in it.
class WorldGenerator
{
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;
	std::vector<Biome> _biomes;
	std::unique_ptr<BiomePlacer> _placer;
	BlocksQueue _blocksQueue;

	int _seed;

	/*static void OptimizeChunkAt(int x, int y, int z, ChunkBlocks& blocks, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);
	void OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;*/

public:

	/// The constructor.
	///	@param seed - the world seed.
	explicit WorldGenerator(int seed);

	/// @brief Adapts chunk at specified origin, according to the world terrain noise.
	///	@details This class transforms chunks by using specified biomes that are incorporated
	///	in the world generator.
	///	@param frame - the frame of the chunk.
	///	@param blocks - the blocks inside the chunk.
	void PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;
};
