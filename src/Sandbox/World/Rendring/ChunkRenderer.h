#pragma once
#include <vector>
#include <glm/vec3.hpp>

#include "RenderViews/RenderView.h"
#include "Sandbox/Camera.h"
#include "Sandbox/World/Chunk/Chunk.h"
#include "Sandbox/World/WorldGenerator.h"

/// @class ChunkRenderer
///	@brief Supports rendering chunks.
/// @details This class is responsible for rendering chunks around the camera by using the algorithms
///	specified in the @link RenderView @endlink
class ChunkRenderer
{
	Log& _log = Log::Get();

	Camera& _camera;
	std::unique_ptr<RenderView> _renderView{};
	WorldGenerator& _generator;

	glm::ivec3 _previousNormalizedPosition;
	std::vector<glm::ivec3> _loadedChunksOrigins = {};
	std::vector<std::unique_ptr<Chunk>> _loadedChunks = {};

	static std::vector<glm::ivec3> Subtract(const std::vector<glm::ivec3>& aSet, const std::vector<glm::ivec3>& bSet);
	glm::ivec3 GetNormalizedPosition(glm::vec3 position) const;
	std::string PositionToString(const glm::ivec3& position) const;

	void RemoveChunkAt(const glm::ivec3& origin);
	void SpawnChunkAt(const glm::ivec3& origin);
	void RenderChunksAround(const glm::ivec3& normalizedOrigin);

public:

	/// @brief The constructor.
	///	@param generator - world generator for chunk building.
	///	@param renderView - to specify which chunks to render.
	///	@param camera - shares a reference point around which the chunks are rendered.
	explicit ChunkRenderer(WorldGenerator& generator, std::unique_ptr<RenderView>& renderView, Camera& camera);

	/// @brief Renders loaded chunks.
	void Render();

	/// @brief Sets the render view.
	///	@param renderView - render view.
	void SetRenderView(std::unique_ptr<RenderView>& renderView);
};


