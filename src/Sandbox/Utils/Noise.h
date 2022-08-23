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

	static std::vector<std::vector<std::vector<float>>> ConvertNoiseFrom1DTo3D(const std::vector<float>& generatedNoise, int chunkSize);

public:
	explicit Noise(const std::string& encodedTree, int seed, float frequency);

	std::vector<float> GetColumnNoise(glm::ivec3 chunkPosition, int chunkSize, int offsetX, int offsetY, int offsetZ) const;
	std::vector<std::vector<std::vector<float>>> GetChunkNoise(glm::ivec3 chunkPosition, int chunkSize) const;
	std::vector<std::vector<std::vector<float>>> GetChunkNoiseWithBorders(glm::ivec3 chunkPosition, int chunkSize) const;
};

