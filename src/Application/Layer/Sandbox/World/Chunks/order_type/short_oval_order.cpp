#include "application/layer/sandbox/world/chunks/order_type/short_oval_order.h"

size_t ShortOvalOrder::GetChunksAmount()
{
	const auto r = static_cast<double>(GetRenderDistance());
	const auto h = static_cast<double>(_height);

	const auto result =  _pi * r * r * (h * 2.0 + 1.0);

	return static_cast<size_t>(result);
}

std::vector<glm::ivec3> ShortOvalOrder::GetChunksAround(const glm::ivec3 normalizedOrigin)
{
	std::vector<glm::ivec3> chunksPositions;

	const auto height = static_cast<int>(_height);
	for (auto y = -height; y <= height; ++y)
	{
		const auto radius = static_cast<int>(GetRenderDistance());
		for (int x = -radius; x <= radius; x++)
		{
			const auto dz = static_cast<int>(sqrt(radius * radius - x * x));
			for (auto z = -dz; z <= dz; z++)
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
