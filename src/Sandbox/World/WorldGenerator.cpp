#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(const int seed)
{
	auto biomeProvider = BiomeProvider("src/Data/Biomes.json");
	_biomes = biomeProvider.GetBiomes(seed);
}
