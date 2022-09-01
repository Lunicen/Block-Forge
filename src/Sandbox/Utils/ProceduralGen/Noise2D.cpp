#include "Noise2D.h"

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

// ReSharper disable once CppMemberFunctionMayBeStatic
float Noise2D::GetNoiseAt(const ChunkFrame&, const int, const int) const
{
	throw LibraryBugException("This feature uses FastNoise2 method (GenSingle2D) that is currently bugged. Please use a workaround (GetNoise function). Link: https://github.com/Auburn/FastNoise2/issues/99");
}

std::vector<std::vector<float>> Noise2D::GetNoise(
	const ChunkFrame& frame, const int xOffset, const int yOffset, const int expansionFactor) const
{
	const auto chunkSize = static_cast<int>(frame.size);
	const auto areaSize = frame.size + static_cast<size_t>(2) * expansionFactor;

	const auto x = frame.origin.x * chunkSize + expansionFactor + xOffset;
	const auto y = frame.origin.y * chunkSize + expansionFactor + yOffset;

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
