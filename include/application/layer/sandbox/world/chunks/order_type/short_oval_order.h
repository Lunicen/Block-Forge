#pragma once
#include "order.h"

/// @class ShortOvalOrder
///	@brief Provides an algorithm for the ChunkPlacer to place the chunks in a short oval manner.
/// @details A short oval is a vertically squashed circle, the final sphere looks like ellipsoid with longer horizontal axis.
class ShortOvalOrder final : public Order
{
	const double _pi = 3.14159265358979323846;
	const size_t _height = 4;

public:
	using Order::Order;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};
