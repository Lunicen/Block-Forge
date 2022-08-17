#pragma once
#include "Biomes/BiomeProvider.h"

class WorldGenerator
{
	std::vector<Biome> _biomes;

public:
	explicit WorldGenerator(int seed);

	void Update();
};
