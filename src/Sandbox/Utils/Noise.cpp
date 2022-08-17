#include "Noise.h"

Noise::Noise(const std::string& encodedTree, const int seed, const float frequency)
	: _seed(seed), _frequency(frequency)
{
	_noiseGenerator = FastNoise::NewFromEncodedNodeTree(encodedTree.c_str());
}

std::vector<float> Noise::GetColumnNoise(const glm::ivec3 chunkPosition, const int chunkSize, const unsigned offsetX, const unsigned offsetZ) const
{
	auto noise = std::vector<float>(chunkSize);

	const auto xPosition = chunkPosition.x + static_cast<int>(offsetX);
	const auto zPosition = chunkPosition.z + static_cast<int>(offsetZ);

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		xPosition , chunkPosition.y, zPosition,
		1, chunkSize, 1,
		_frequency, _seed);

	return noise;
}

std::vector<float> Noise::GetChunkNoise(const glm::ivec3 chunkPosition, const int chunkSize) const
{
	auto noise = std::vector<float>(chunkSize * chunkSize * chunkSize);

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		chunkPosition.x, chunkPosition.y, chunkPosition.z,
		chunkSize, chunkSize, chunkSize,
		_frequency, _seed);

	return noise;
}
