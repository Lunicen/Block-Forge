#pragma once
#include "Biome.h"
#include "Sandbox/Utils/ProceduralGen/Noise2D.h"

class BiomePlacer
{
	Log& _log = Log::Get();

	Noise2D _noise;
	std::vector<Biome>& _biomes;

	bool HasChunkOnlySingleBiome(glm::ivec3 origin, int size) const;
	Biome& GetBiomeAt(float noise) const;
	
public:
	
	explicit BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes);

	
	void PaintChunk(glm::ivec3 origin, ChunkData& chunk, int size) const;

	std::vector<std::vector<std::vector<float>>> GetChunkNoiseWithBorders(glm::ivec3 origin, int size) const;
};

