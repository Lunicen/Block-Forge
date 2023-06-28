#include "application/layer/sandbox/world/chunks/order_type/tilted_cube_order.h"

size_t TiltedCubeOrder::GetChunksAmount()
{
	const auto& dimension = GetRenderDistance() * 2 + 1;
	return dimension * dimension * dimension;
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
					x + normalizedOrigin.x,
					y + normalizedOrigin.y,
					z + normalizedOrigin.z
				);
			}
		}
	}

	return chunksPositions;
}
