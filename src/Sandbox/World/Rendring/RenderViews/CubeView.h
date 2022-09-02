#pragma once
#include "RenderView.h"

/// @class CubeView
///	@brief Provides an algorithm that the renderer renders chunks in as a cube.
/// @details Basically this algorithm returns origins formed in a cube.
class CubeView final : public RenderView
{
public:

	/// @brief The constructor.
	///	@param renderDistance - the maximum distance from the camera to render.
	///	@param chunkSize - the size of the generated chunks.
	CubeView(const size_t& renderDistance, const size_t& chunkSize)
		: RenderView(renderDistance, chunkSize)
	{
	}

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

