#pragma once
#define FASTNOISE_STATIC_LIB 1

#include <vector>
#include <FastNoise/FastNoise.h>
#include <glm/vec3.hpp>

#include "Core/Log.h"

class Noise
{
	Log& _log = Log::Get();

	const int _seed;
	unsigned _chunkSize;
	FastNoise::SmartNode<> _noiseGenerator;

public:
	
	explicit Noise(const std::string& encodedTree, int seed, unsigned chunkSize);

	std::vector<float> GetColumnNoise(glm::ivec3 chunkPosition, unsigned offsetX, unsigned offsetZ) const;
	std::vector<float> GetChunkNoise(glm::ivec3 chunkPosition) const;

	void SetChunkSize(unsigned chunkSize);
};

