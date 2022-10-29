#include "DiamondOrder.h"

size_t DiamondOrder::CountChunksRecursive(const size_t level)
{
	const auto result = 4 * level;

	if (result == 0) return 1;
	return result + CountChunksRecursive(level - 1);
}

size_t DiamondOrder::GetChunksAmount()
{
	auto distance = GetRenderDistance();

	auto chunksAmount = CountChunksRecursive(GetRenderDistance());
	while (distance--)
	{
		constexpr auto diamondSides = 2;
		chunksAmount += CountChunksRecursive(distance) * diamondSides;
	}

	return chunksAmount;
}

std::vector<glm::ivec3> DiamondOrder::GetChunksAround(const glm::ivec3 normalizedOrigin)
{
	std::vector<glm::ivec3> chunksPositions;

	const auto yBound = static_cast<int>(GetRenderDistance());
	for (auto y = -yBound; y <= yBound; ++y)
	{
		const auto xBound = yBound - abs(y);
		for (auto x = -xBound; x <= xBound; ++x)
		{
			const auto zBound = abs(abs(x) + abs(y) - yBound);
			for (auto z = -zBound; z <= zBound; ++z)
			{
				chunksPositions.emplace_back(
					glm::ivec3(x + normalizedOrigin.x,
							   y + normalizedOrigin.y,
							   z + normalizedOrigin.z)
				);
			}
		}
	}

	return chunksPositions;
}
