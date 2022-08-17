#include "BiomeProvider.h"

BiomeProvider::BiomeProvider(const std::string& filenameWithBiomeData)
{
	_biomesMetadata.Load(filenameWithBiomeData);
}

std::vector<Biome> BiomeProvider::GetBiomes(const int seed, const std::string& biomesType)
{
	if (!_biomesMetadata.IsLoaded()) throw std::runtime_error("Biome data is not loaded!");

	auto biomesPool = _biomesMetadata.GetJsonArray(biomesType);
	auto biomes = std::vector<Biome>();

	for (auto& biome : biomesPool)
	{
		const auto name = biome["name"].get<std::string>();

		const auto id = biome["noise"]["id"].get<std::string>();
		const auto frequency = biome["noise"]["frequency"].get<float>();

		biomes.emplace_back(name, Noise(id, seed, frequency));
	}

	return biomes;
}
