#pragma once
#include "Biome.h"
#include "Sandbox/Utils/Chunk/ChunkFrame.h"
#include "Sandbox/Utils/ProceduralGen/Noise2D.h"

class BiomePlacer
{
	Log& _log = Log::Get();

	Noise2D _noise;
	std::vector<Biome>& _biomes;

	static bool HasChunkOnlySingleBiome(const std::vector<std::vector<float>>& biomesMap);
	Biome& GetBiomeAt(float noise) const;
	
public:
	
	explicit BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes);

	void PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;

	std::vector<std::vector<std::vector<float>>> GetChunkNoise(const ChunkFrame& frame, int expansionFactor = 0) const;
};

