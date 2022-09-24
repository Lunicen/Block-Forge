#pragma once
#include "RenderView.h"

/// @class CubeView
///	@brief Provides an algorithm that the renderer renders chunks in as a cube.
/// @details Basically this algorithm returns origins formed in a cube.
class CubeView final : public RenderView
{
public:
	using RenderView::RenderView;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

