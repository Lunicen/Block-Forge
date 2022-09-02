#pragma once
#include <vector>
#include <glm/vec3.hpp>

class RenderView  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:
	size_t _renderDistance;
	size_t _chunkSize;

public:
	RenderView(const size_t& renderDistance, const size_t& chunkSize)
	{
		_renderDistance = renderDistance;
		_chunkSize = chunkSize;
	}

	void SetRenderDistance(const size_t& renderDistance)
	{
		_renderDistance = renderDistance;
	}

	void SetChunkSize(const size_t& chunkSize)
	{
		_chunkSize = chunkSize;
	}

	size_t GetChunkSize() const
	{
		return _chunkSize;
	}

	/// @brief Get the amount of chunks that could be generated on the current render distance settings.
	virtual size_t GetChunksAmount() = 0;
	virtual std::vector<glm::ivec3> GetChunksAround(glm::ivec3 origin) = 0;

	virtual ~RenderView() = default;
};
