#pragma once
#include "Biomes/BiomeProvider.h"

class WorldGenerator
{
	std::vector<Biome> _biomes;
	int _seed;

	static void PrepareForPainting(std::vector<std::vector<std::vector<Block*>>>& blocks, int vectorSize);

public:
	explicit WorldGenerator(int seed);

	void Initialize(Shader& blockShader);
	std::vector<std::vector<std::vector<Block*>>> GetPaintedChunkWithBorders(glm::ivec3 chunkOrigin, int chunkSize) const;
	bool IsInitialized() const;
};
