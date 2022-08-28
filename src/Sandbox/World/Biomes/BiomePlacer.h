#pragma once
#include "Biome.h"
#include "Sandbox/Utils/ProceduralGen/Noise2D.h"

class BiomePlacer
{
	Log& _log = Log::Get();

	const int _seed;
	Noise2D _noise;
	std::vector<Biome>& _biomes;

public:
	
	explicit BiomePlacer(int seed, const Noise2D& noise2D, std::vector<Biome>& biomes);
};

