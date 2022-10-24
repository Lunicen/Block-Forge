#include "TiltedCubeOrder.h"

size_t TiltedCubeOrder::GetChunksAmount()
{
	const auto& r = GetRenderDistance() * 2 + 1;
	return (r + 1) * ((r + 1) * (r + 1) + r * r);
}

std::vector<glm::ivec3> TiltedCubeOrder::GetChunksAround(const glm::ivec3 normalizedOrigin)
{
	std::vector<glm::ivec3> chunksPositions;

	const auto bound = static_cast<int>(GetRenderDistance());
	for (auto x = -bound; x <= bound; ++x)
	{
		for (auto y = -bound; y <= bound; ++y)
		{
			const auto zBound = abs(bound - abs(x));
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
