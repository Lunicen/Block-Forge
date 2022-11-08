#pragma once
#include "Order.h"

class ShortOvalOrder final : public Order
{
	const double _pi = 3.14159265358979323846;
	const size_t _height = 4;

public:
	using Order::Order;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};
