#pragma once
#include "application/layer/sandbox/world/biomes/biome_placer.h"
#include "application/layer/sandbox/world/biomes/biome_provider.h"

/// @class WorldGenerator
/// @brief Handles generating the world.
///	@details This class is made for transforming chunks according to the biomes that are specified in it.
class WorldGenerator
{
	std::vector<Biome> _biomes;
	std::unique_ptr<BiomePlacer> _placer;
	BlockMap _blockMap = BlockMap("src/Data/Blocks.json");

	int _seed;

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

	/// @brief Returns the map of blocks used by this generator.
	BlockMap& GetBlockMap();
};
