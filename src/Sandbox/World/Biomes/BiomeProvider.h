#pragma once
#include "Biome.h"
#include "Core/Metadata.h"

class BiomeProvider
{
	Metadata _biomesMetadata;
	Shader& _blockShader;

public:
	explicit BiomeProvider(const std::string& filenameWithBiomeData, Shader& blockShader);

	std::vector<Biome> GetBiomes(int seed, const std::string& biomesType = "default");
};

