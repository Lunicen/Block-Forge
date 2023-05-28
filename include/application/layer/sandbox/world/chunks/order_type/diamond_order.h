#pragma once
#include "order.h"

/// @class DiamondOrder
/// @brief Provides an algorithm for the ChunkPlacer to place the chunks in a diamond manner.
///	@note <a href="https://en.wikipedia.org/wiki/Diamond_graph">Here</a> is the explanation.
class DiamondOrder final : public Order
{
	static size_t CountChunksRecursive(size_t level);

public:
	using Order::Order;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

