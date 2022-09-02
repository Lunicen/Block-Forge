#pragma once
#include "RenderView.h"

class TiltedCube final : public RenderView
{
public:
	TiltedCube(const size_t& renderDistance, const size_t& chunkSize)
		: RenderView(renderDistance, chunkSize)
	{
	}

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

