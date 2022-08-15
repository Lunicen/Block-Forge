#include "Noise.h"

Noise::Noise(const std::string& encodedTree, const int seed, const unsigned chunkSize)
	: _seed(seed), _chunkSize(chunkSize)
{
	_noiseGenerator = FastNoise::NewFromEncodedNodeTree(encodedTree.c_str());
}

std::vector<float> Noise::GetColumnNoise(const glm::ivec3 chunkPosition, unsigned offsetX, unsigned offsetZ) const
{
	auto noise = std::vector<float>(_chunkSize);

	const auto xPosition = chunkPosition.x + static_cast<int>(offsetX);
	const auto zPosition = chunkPosition.z + static_cast<int>(offsetZ);

	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		xPosition , chunkPosition.y, zPosition,
		1, _chunkSize, 1,
		1.0f, _seed);

	return noise;
}

std::vector<float> Noise::GetChunkNoise(const glm::ivec3 chunkPosition) const
{
	auto noise = std::vector<float>(_chunkSize * _chunkSize * _chunkSize);
	
	_noiseGenerator->GenUniformGrid3D(
		noise.data(),
		chunkPosition.x, chunkPosition.y, chunkPosition.z,
		_chunkSize, _chunkSize, _chunkSize,
		1.0f, _seed);

	return noise;
}

void Noise::SetChunkSize(const unsigned chunkSize)
{
	_chunkSize = chunkSize;
}
