#include "application/layer/sandbox/noise/noise2d.h"

std::vector<std::vector<float>> Noise2D::ConvertNoiseFrom1DTo2D(const std::vector<float>& noise, const size_t& size)
{
	std::vector<std::vector<float>> result;
	auto index = 0;

	result.resize(size);
	for (size_t x = 0; x < size; ++x)
	{
		result[x].resize(size);
	}

	for (size_t y = 0; y < size; ++y)
	{
		for (size_t x = 0; x < size; ++x)
		{
			result[x][y] = noise[index];
			++index;
		}
	}

	return result;
}

float Noise2D::GetNoiseAt(const ChunkFrame& frame, const int xOffset, const int yOffset) const
{
	// The reason why these values must be multiplied by the frequency
	// is due to the fact of an inconsistency in the noise library interface
	// https://github.com/Auburn/FastNoise2/issues/99#issuecomment-1232627339
	const auto x = static_cast<float>(frame.origin.x * frame.size + xOffset) * GetFrequency();
	const auto y = static_cast<float>(frame.origin.z * frame.size + yOffset) * GetFrequency();

	return GetGenerator()->GenSingle2D(x, y, GetSeed());
}

std::vector<std::vector<float>> Noise2D::GetNoise(
	const ChunkFrame& frame, const int xOffset, const int yOffset, const int expansionFactor) const
{
	const auto chunkSize = static_cast<int>(frame.size);
	const auto areaSize = frame.size + static_cast<size_t>(2) * expansionFactor;

	const auto x = frame.origin.x * chunkSize - expansionFactor + xOffset;
	const auto y = frame.origin.z * chunkSize - expansionFactor + yOffset;

	auto noise = std::vector<float>(areaSize * areaSize);

	GetGenerator()->GenUniformGrid2D(
		noise.data(),
		x, y,
		static_cast<int>(areaSize), static_cast<int>(areaSize),
		GetFrequency(), GetSeed());

	return ConvertNoiseFrom1DTo2D(noise, areaSize);
}

std::vector<std::vector<float>> Noise2D::GetNoise(const ChunkFrame& frame, const int expansionFactor) const
{
	return GetNoise(frame, 0, 0, expansionFactor);
}
