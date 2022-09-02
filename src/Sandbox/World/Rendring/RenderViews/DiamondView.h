#pragma once
#include "RenderView.h"

/// @class DiamondView
///	@brief Provides an algorithm that the renderer renders chunks in as a diamond.
///	@note <a href="https://en.wikipedia.org/wiki/Diamond_graph">Here</a> is the explanation.
class DiamondView final : public RenderView
{
	static size_t CountChunksRecursive(size_t level);

public:

	/// @brief The constructor.
	///	@param renderDistance - the maximum distance from the camera to render.
	///	@param chunkSize - the size of the generated chunks.
	DiamondView(const size_t& renderDistance, const size_t& chunkSize)
		: RenderView(renderDistance, chunkSize)
	{
	}

	size_t GetChunksAmount() override;
	std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) override;
};

