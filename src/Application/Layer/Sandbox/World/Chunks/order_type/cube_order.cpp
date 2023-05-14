#include "application/layer/sandbox/world/chunks/order_type/cube_order.h"

size_t CubeOrder::GetChunksAmount()
{
	const auto& dimension = GetRenderDistance() * 2 + 1;
	return dimension * dimension * dimension;
}

std::vector<glm::ivec3> CubeOrder::GetChunksAround(const glm::ivec3 normalizedOrigin)
{
	std::vector<glm::ivec3> chunksPositions;

	const auto bound = static_cast<int>(GetRenderDistance());
	for (auto x = -bound; x <= bound; ++x)
	{
		for (auto y = -bound; y <= bound; ++y)
		{
			for (auto z = -bound; z <= bound; ++z)
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
