#pragma once
#include <vector>
#include <glm/vec3.hpp>

/// @class RenderView
///	@brief The base class for creating render views.
///	@details A render view is a class providing the algorithm, by which
///	the chunks are rendered.
class RenderView  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:

	///	@brief the maximum distance from the camera to render.
	size_t _renderDistance;

	///	@brief the size of the generated chunks.
	size_t _chunkSize;

public:

	/// @brief The constructor.
	///	@param renderDistance - the maximum distance from the camera to render.
	///	@param chunkSize - the size of the generated chunks.
	RenderView(const size_t& renderDistance, const size_t& chunkSize)
	{
		_renderDistance = renderDistance;
		_chunkSize = chunkSize;
	}

	/// @brief Sets render distance.
	///	@param renderDistance - the maximum distance from the camera to render.
	void SetRenderDistance(const size_t& renderDistance)
	{
		_renderDistance = renderDistance;
	}

	/// @brief Sets chunk size.
	///	@param chunkSize - the size of the generated chunks.
	void SetChunkSize(const size_t& chunkSize)
	{
		_chunkSize = chunkSize;
	}

	/// @brief Returns chunk size.
	size_t GetChunkSize() const
	{
		return _chunkSize;
	}

	/// @brief Returns the chunks amount that are rendered within this render view.
	virtual size_t GetChunksAmount() = 0;


	/// @brief Get the amount of chunks that could be generated on the current render distance settings.
	virtual std::vector<glm::ivec3> GetChunksAround(glm::ivec3 normalizedOrigin) = 0;

	virtual ~RenderView() = default;
};
