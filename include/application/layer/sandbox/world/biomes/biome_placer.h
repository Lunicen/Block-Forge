#pragma once
#include "biome.h"
#include "application/layer/sandbox/noise/noise2d.h"

/// @class BiomePlacer
/// @brief Places biomes according to the biomes map.
///	@details This class decides which biome to generate according to the noise algorithm, that represents the world map.
class BiomePlacer
{
	Log& _log = Log::Get();

	Noise2D _noise;
	std::vector<Biome>& _biomes;

	static bool HasChunkOnlySingleBiome(const std::vector<std::vector<float>>& biomesMap);
	Biome& GetBiomeAt(float noise) const;
	[[nodiscard]] static Byte GetBlockVisibilityFlags(const Position& origin, const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders);
	static bool IsAir(const Position& origin, const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders);

	void PaintBlockAt(const Position& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders, const std::vector<std::vector<float>>& biomesMapNoise) const;

public:

	/// @brief The constructor.
	///	@param noise2D - represents the world map, so how the biomes are placed in the world.
	///	@param biomes - the biomes that are meant to be placed.
	explicit BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes);

	
	/// @brief Paints the chunk according to the world map.
	///	@details This method modifies the blockAt data according by deciding based on biomes placed on the map.
	///	@param frame - the frame of the chunk.
	///	@param blocks - the blockAt inside the chunk.
	void PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;

	/// @brief Returns the noise of the chunk.
	///	@details This method returns the noise of the chunk that contains the biomes according to the world map.
	///	@param frame - the frame of the chunk.
	/// @param expansionFactor - the factor that expands or shrinks the dimensions of the chunk.
	std::vector<std::vector<std::vector<float>>> GetChunkNoise(const ChunkFrame& frame, int expansionFactor = 0) const;
};

