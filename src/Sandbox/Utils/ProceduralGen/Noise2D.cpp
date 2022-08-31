#include "Noise2D.h"

std::vector<std::vector<float>> Noise2D::ConvertNoiseFrom1DTo2D(const std::vector<float>& noise, int size)
{
	const auto& planeSize = static_cast<size_t>(size);
	std::vector<std::vector<float>> result;
	auto index = 0;

	result.resize(planeSize);
	for (size_t x = 0; x < planeSize; ++x)
	{
		result[x].resize(planeSize);
	}

	for (size_t y = 0; y < planeSize; ++y)
	{
		for (size_t x = 0; x < planeSize; ++x)
		{
			result[x][y] = noise[index];
			++index;
		}
	}

	return result;
}

std::vector<std::vector<float>> Noise2D::GetNoise(const glm::ivec2 origin, const int size) const
{
	auto noise = std::vector<float>(static_cast<unsigned>(size * size));

	const auto x = origin.x * size;
	const auto y = origin.y * size;

	_noiseGenerator->GenUniformGrid2D(
		noise.data(),
		x, y,
		size, size,
		_frequency, _seed);

	return ConvertNoiseFrom1DTo2D(noise, size);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
float Noise2D::GetNoiseAt(const glm::ivec2 origin, const int size, const int xOffset, const int yOffset) const
{
	throw LibraryBugException("This feature uses FastNoise2 method (GenSingle2D) that is currently bugged. Please use a workaround (GetNoise function). Link: https://github.com/Auburn/FastNoise2/issues/99");
}
