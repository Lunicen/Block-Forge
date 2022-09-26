#include "Noise3D.h"

#include "Core/EngineExceptions.h"

glm::ivec3 Noise3D::GetOriginShiftedByExpansionFactor(
	const ChunkFrame& frame, 
	const int xOffset, const int yOffset, const int zOffset,
	const int expansionFactor)
{
	glm::ivec3 result;

	result.x = frame.origin.x * static_cast<int>(frame.size) - expansionFactor + xOffset;
	result.y = frame.origin.y * static_cast<int>(frame.size) - expansionFactor + yOffset;
	result.z = frame.origin.z * static_cast<int>(frame.size) - expansionFactor + zOffset;

	return result;
}

std::vector<std::vector<std::vector<float>>> Noise3D::ConvertNoiseFrom1DTo3D(const std::vector<float>& noise, const size_t& size)
{
	std::vector<std::vector<std::vector<float>>> result;
	auto index = 0;

	result.resize(size);
	for (size_t x = 0; x < size; ++x)
	{
		result[x].resize(size);
		for (size_t y = 0; y < size; ++y)
		{
			result[x][y].resize(size);
		}
	}

	for (size_t z = 0; z < size; ++z)
	{
		for (size_t y = 0; y < size; ++y)
		{
			for (size_t x = 0; x < size; ++x)
			{
				result[x][y][z] = noise[index];
				++index;
			}
		}
	}

	return result;
}

void Noise3D::ValidateDataCorrectness(const size_t& noiseSize)
{
	constexpr auto minimalSupportedNoiseSize = 8;
	if (noiseSize < minimalSupportedNoiseSize)
	{
		throw LibraryBugException("FastNoise2 library does not supporting sizes smaller than " + std::to_string(minimalSupportedNoiseSize) + " for 3D noise generation. Link: https://github.com/Auburn/FastNoise2/issues/89");
	}
}

std::vector<float> Noise3D::GetColumnNoiseWithAdditionalHeight(
	const ChunkFrame& frame, 
	const int xOffset, const int yOffset, const int zOffset,
	const size_t additionalHeight) const
{
	ValidateDataCorrectness(frame.size);

	const auto origin = GetOriginShiftedByExpansionFactor(frame, xOffset, yOffset, zOffset, 0);
	const auto areaSize = frame.size + additionalHeight;

	auto noise = std::vector<float>(areaSize);

	GetGenerator()->GenUniformGrid3D(
		noise.data(),
		origin.x, origin.y, origin.z,
		1, static_cast<int>(areaSize), 1,
		GetFrequency(), GetSeed());

	return noise;
}

std::vector<float> Noise3D::GetColumnNoise(
	const ChunkFrame& frame, 
	const int xOffset, const int yOffset, const int zOffset, 
	const int expansionFactor) const
{
	ValidateDataCorrectness(frame.size);

	const auto origin = GetOriginShiftedByExpansionFactor(frame, xOffset, yOffset, zOffset, expansionFactor);
	const auto areaSize = frame.size + static_cast<size_t>(2) * expansionFactor;

	auto noise = std::vector<float>(areaSize);

	GetGenerator()->GenUniformGrid3D(
		noise.data(),
		origin.x, origin.y, origin.z,
		1, static_cast<int>(areaSize), 1,
		GetFrequency(), GetSeed());

	return noise;
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoise(
	const ChunkFrame& frame, const int xOffset, const int yOffset, const int zOffset, const int expansionFactor) const
{
	const auto areaSize = frame.size + static_cast<size_t>(2) * expansionFactor;
	const auto origin = GetOriginShiftedByExpansionFactor(frame, xOffset, yOffset, zOffset, expansionFactor);

	auto noise = std::vector<float>(areaSize * areaSize * areaSize);

	GetGenerator()->GenUniformGrid3D(
		noise.data(),
		origin.x, origin.y, origin.z,
		static_cast<int>(areaSize), static_cast<int>(areaSize), static_cast<int>(areaSize),
		GetFrequency(), GetSeed());

	return ConvertNoiseFrom1DTo3D(noise, areaSize);
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoise(const ChunkFrame& frame, const int expansionFactor) const
{
	return GetNoise(frame, 0, 0, 0, expansionFactor);
}
