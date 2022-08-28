#include "Noise3D.h"

std::vector<std::vector<std::vector<float>>> Noise3D::ConvertNoiseFrom1DTo3D(const std::vector<float>& generatedNoise,
                                                                             const int chunkSize)
{
	const auto& size = static_cast<size_t>(chunkSize);
	std::vector<std::vector<std::vector<float>>> result;
	result.reserve(generatedNoise.size());
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
				result[x][y][z] = generatedNoise[index];
				++index;
			}
		}
	}

	return result;
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoise(const glm::ivec3 origin, const int size) const
{
	auto noise = std::vector<float>(static_cast<unsigned>(size * size * size));

	const auto x = origin.x * size;
	const auto y = origin.y * size;
	const auto z = origin.z * size;

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		size, size, size,
		_frequency, _seed);

	return ConvertNoiseFrom1DTo3D(noise, size);
}

std::vector<std::vector<std::vector<float>>> Noise3D::GetNoiseWithBorders(const glm::ivec3 origin, const int size) const
{
	const auto sizeWithBorders = size + 2;
	auto noise = std::vector<float>(static_cast<unsigned>(sizeWithBorders * sizeWithBorders * sizeWithBorders));

	const auto x = origin.x * size - 1;
	const auto y = origin.y * size - 1;
	const auto z = origin.z * size - 1;

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		sizeWithBorders, sizeWithBorders, sizeWithBorders,
		_frequency, _seed);

	return ConvertNoiseFrom1DTo3D(noise, sizeWithBorders);
}
