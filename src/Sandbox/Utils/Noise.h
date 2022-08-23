#pragma once
#define FASTNOISE_STATIC_LIB 1

#include <vector>
#include <FastNoise/FastNoise.h>
#include <glm/vec3.hpp>

#include "Core/Log.h"

/// @class Noise
/// @brief Represents noise algorithm that is basically used for terrain generation.
class Noise
{
	Log& _log = Log::Get();

	const int _seed;
	const float _frequency;
	FastNoise::SmartNode<> _noiseGenerator;

	static std::vector<std::vector<std::vector<float>>> ConvertNoiseFrom1DTo3D(const std::vector<float>& generatedNoise, int chunkSize);

public:

	/// @brief The constructor.
	///	@param encodedTree - A string with encoded tree generated by using FastNoise2 tool.
	///	@param seed - noise seed for different results.
	///	@param frequency - The frequency of the encoded noise function.
	explicit Noise(const std::string& encodedTree, int seed, float frequency);

	/// @brief Get chunk noise that is at certain position on the map.
	/// @param origin - origin of the chunk.
	/// @param size - the size of the chunk (in one dimension).
	std::vector<std::vector<std::vector<float>>> GetChunkNoise(glm::ivec3 origin, int size) const;

	/// @brief Get chunk noise that is at certain position on the map, including the noise around it.
	/// @param origin - origin of the chunk.
	/// @param size - the size of the chunk (in one dimension).
	std::vector<std::vector<std::vector<float>>> GetChunkNoiseWithBorders(glm::ivec3 origin, int size) const;
};

