#include "Noise3D.h"

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

std::vector<float> Noise3D::GetColumnNoise(
	const ChunkFrame& frame, const int xOffset, const int yOffset, const int zOffset, const int expansionFactor) const
{
	if (frame.size < 8)
	{
		throw LibraryBugException("FastNoise2 library does not supporting sizes smaller than 8 for 3D noise generation. Link: https://github.com/Auburn/FastNoise2/issues/89");
	}

	const auto chunkSize = static_cast<int>(frame.size);

	const auto x = frame.origin.x * chunkSize + expansionFactor + xOffset;
	const auto y = frame.origin.y * chunkSize + expansionFactor + yOffset;
	const auto z = frame.origin.z * chunkSize + expansionFactor + zOffset;

	const auto areaSize = frame.size + static_cast<size_t>(2 * expansionFactor);
	auto noise = std::vector<float>(areaSize);

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		1, static_cast<int>(areaSize), 1,
		_frequency, _seed);

	return noise;
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoise(
	const ChunkFrame& frame, const int xOffset, const int yOffset, const int zOffset, const int expansionFactor) const
{
	const auto chunkSize = static_cast<int>(frame.size);
	const auto areaSize = frame.size + static_cast<size_t>(2 * expansionFactor);

	const auto x = frame.origin.x * chunkSize + expansionFactor + xOffset;
	const auto y = frame.origin.y * chunkSize + expansionFactor + yOffset;
	const auto z = frame.origin.z * chunkSize + expansionFactor + zOffset;

	auto noise = std::vector<float>(areaSize * areaSize * areaSize);

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		static_cast<int>(areaSize), static_cast<int>(areaSize), static_cast<int>(areaSize),
		_frequency, _seed);

	return ConvertNoiseFrom1DTo3D(noise, areaSize);
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoise(const ChunkFrame& frame, const int expansionFactor) const
{
	return GetNoise(frame, 0, 0, 0, expansionFactor);
}
