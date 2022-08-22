#include "Noise.h"

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

std::vector<float> Noise::GetChunkNoise(const glm::ivec3 chunkPosition, const int chunkSize) const
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

	return noise;
}
