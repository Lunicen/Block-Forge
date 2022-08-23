#include "Noise.h"

std::vector<std::vector<std::vector<float>>> Noise::ConvertNoiseFrom1DTo3D(const std::vector<float>& generatedNoise, const int chunkSize)
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
				result[x][y][z] = generatedNoise[index++];
			}
		}
	}

	return result;
}

Noise::Noise(const std::string& encodedTree, const int seed, const float frequency)
	: _seed(seed), _frequency(frequency)
{
	_noiseGenerator = FastNoise::NewFromEncodedNodeTree(encodedTree.c_str());
}

std::vector<float> Noise::GetColumnNoise(const glm::ivec3 chunkPosition, const int chunkSize, const int offsetX, const int offsetY, const int offsetZ) const
{
	auto noise = std::vector<float>(chunkSize);

	const auto xPosition = chunkPosition.x * chunkSize + offsetX;
	const auto yPosition = chunkPosition.y * chunkSize + offsetY;
	const auto zPosition = chunkPosition.z * chunkSize + offsetZ;

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		xPosition , yPosition, zPosition,
		1, chunkSize, 1,
		_frequency, _seed);

	return noise;
}

std::vector<std::vector<std::vector<float>>> Noise::GetChunkNoise(const glm::ivec3 chunkPosition, const int chunkSize) const
{
	auto noise = std::vector<float>(chunkSize * chunkSize * chunkSize);

	const auto x = chunkPosition.x * chunkSize;
	const auto y = chunkPosition.y * chunkSize;
	const auto z = chunkPosition.z * chunkSize;

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		chunkSize, chunkSize, chunkSize,
		_frequency, _seed);

	return ConvertNoiseFrom1DTo3D(noise, chunkSize);
}

std::vector<std::vector<std::vector<float>>> Noise::GetChunkNoiseWithBorders(const glm::ivec3 chunkPosition, const int chunkSize) const
{
	const auto chunkSizeWithBorders = chunkSize + 2;
	auto noise = std::vector<float>(chunkSizeWithBorders * chunkSizeWithBorders * chunkSizeWithBorders);

	const auto x = chunkPosition.x * chunkSize - 1;
	const auto y = chunkPosition.y * chunkSize - 1;
	const auto z = chunkPosition.z * chunkSize - 1;

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		x, y, z,
		chunkSizeWithBorders, chunkSizeWithBorders, chunkSizeWithBorders,
		_frequency, _seed);

	return ConvertNoiseFrom1DTo3D(noise, chunkSizeWithBorders);
}
