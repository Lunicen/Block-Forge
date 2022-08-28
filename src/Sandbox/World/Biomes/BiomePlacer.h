#pragma once
#include "Biome.h"
#include "Sandbox/Utils/ProceduralGen/Noise2D.h"

class BiomePlacer
{
	Log& _log = Log::Get();

	Noise2D _noise;
	std::vector<Biome>& _biomes;

	bool HasChunkOnlySingleBiome(glm::ivec3 origin, int size) const;
	static void PaintChunkWithBiome(glm::ivec3 origin, ChunkData& chunk, int size, const Biome& biome);
	
public:
	
	explicit BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes);

	void PaintChunk(glm::ivec3 origin, ChunkData& chunk, int size);
};

