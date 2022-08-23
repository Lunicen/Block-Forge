#pragma once
#include "Biomes/BiomeProvider.h"

class WorldGenerator
{
	std::vector<Biome> _biomes;
	int _seed;

	static void OptimizeChunkAt(int x, int y, int z, ChunkData& data, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);
	static void OptimizeChunk(ChunkData& data, const std::vector<std::vector<std::vector<float>>>& noiseOfChunkWithBorders);

public:
	explicit WorldGenerator(int seed);

	void Initialize(Shader& blockShader);
	void PaintChunk(ChunkData& chunk, glm::ivec3 origin, int size) const;
	bool IsInitialized() const;
};
