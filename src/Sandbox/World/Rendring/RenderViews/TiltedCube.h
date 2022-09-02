#pragma once
#include "RenderView.h"

/// @class TiltedCube
///	@brief Provides an algorithm that the renderer renders chunks in as a tilted cube.
/// @details A tilted cube is just a cube that it's edges are pointing cardinal directions.
class TiltedCube final : public RenderView
{
public:
	using RenderView::RenderView;

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

