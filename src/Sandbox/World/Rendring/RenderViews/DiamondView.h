#pragma once
#include "RenderView.h"

class DiamondView final : public RenderView
{
	static size_t CountChunksRecursive(size_t level);

public:
	DiamondView(const size_t& renderDistance, const size_t& chunkSize)
		: RenderView(renderDistance, chunkSize)
	{
	}

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedPosition) override;
};

