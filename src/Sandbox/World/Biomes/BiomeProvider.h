#pragma once
#include "Biome.h"
#include "Core/Metadata.h"

class BiomeProvider
{
	Metadata _biomesMetadata;

public:
	explicit BiomeProvider(const std::string& filenameWithBiomeData);

	std::vector<Biome> GetBiomes(int seed, const std::string& biomesType = "default");
};

