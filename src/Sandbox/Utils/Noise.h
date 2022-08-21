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
	const float _frequency;
	FastNoise::SmartNode<> _noiseGenerator;

public:
	explicit Noise(const std::string& encodedTree, int seed, float frequency);

	std::vector<float> GetColumnNoise(glm::ivec3 chunkPosition, int chunkSize, int offsetX, int offsetY, int offsetZ) const;
	std::vector<float> GetChunkNoise(glm::ivec3 chunkPosition, int chunkSize) const;

	std::vector<float> GetSurfaceNoiseXY(glm::ivec3 chunkPosition, int chunkSize, int yLevel) const;
	std::vector<float> GetSurfaceNoiseYZ(glm::ivec3 chunkPosition, int chunkSize, int xLevel) const;
	std::vector<float> GetSurfaceNoiseXZ(glm::ivec3 chunkPosition, int chunkSize, int zLevel) const;
};

