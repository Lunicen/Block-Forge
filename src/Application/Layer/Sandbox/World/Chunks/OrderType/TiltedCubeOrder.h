#pragma once
#include "Order.h"

/// @class TiltedCubeOrder
///	@brief Provides an algorithm for the ChunkPlacer to place the chunks in a tilted cube manner.
/// @details A tilted cube is just a regular cube that it's edges are pointing cardinal directions.
class TiltedCubeOrder final : public Order
{
public:
	using Order::Order;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

