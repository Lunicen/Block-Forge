#include "BiomePlacer.h"

BiomePlacer::BiomePlacer(const int seed, const Noise2D& noise2D, std::vector<Biome>& biomes) : _seed(seed), _noise(noise2D), _biomes(biomes)
{
}
