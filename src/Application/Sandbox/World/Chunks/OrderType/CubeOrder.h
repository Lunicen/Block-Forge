#pragma once
#include "Order.h"

/// @class CubeOrder
/// @brief Provides an algorithm for the ChunkPlacer to place the chunks in a cube manner.
/// @details Basically this algorithm returns origins formed in a cube.
class CubeOrder final : public Order
{
public:
	using Order::Order;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

