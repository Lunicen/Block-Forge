#pragma once
#include "Sandbox/World/ChunkData.h"

class ChunkUtils
{
public:
	static float CalculateMidPoint(int chunkSize);
	static ChunkData InitializeData(int chunkSize);

	template <typename Type>
	static std::vector<std::vector<std::vector<Type>>> Chunkify(std::vector<Type> vector, int chunkSize);
};

template <typename Type>
std::vector<std::vector<std::vector<Type>>> ChunkUtils::Chunkify(std::vector<Type> vector, const int chunkSize)
{
	/*if (chunkSize * chunkSize * chunkSize != vector.size())
	{
		throw std::runtime_error("Cannot chunkify the given vector!");
	}

	std::vector<std::vector<std::vector<Type>>> result;
	result.resize(chunkSize);
	for (auto x = 0; x < chunkSize; ++x)
	{
		result[x].resize(chunkSize);
		for (auto y = 0; y < chunkSize; ++y)
		{
			result[x][y].resize(chunkSize);
		}
	}*/

	return std::vector<std::vector<std::vector<Type>>>();
}

