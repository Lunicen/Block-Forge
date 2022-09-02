#pragma once
#include <vector>
#include <glm/vec3.hpp>

#include "RenderViews/RenderView.h"
#include "Sandbox/Camera.h"
#include "Sandbox/World/Chunk.h"
#include "Sandbox/World/WorldGenerator.h"

class ChunkRenderer
{
	Log& _log = Log::Get();

	Camera& _camera;
	std::unique_ptr<RenderView> _renderView;
	WorldGenerator& _generator;

	glm::ivec3 _previousNormalizedPosition;
	std::vector<glm::ivec3> _loadedChunksOrigins = {};
	std::vector<std::unique_ptr<Chunk>> _loadedChunks = {};

	glm::ivec3 GetNormalizedPosition(glm::vec3 position) const;
	std::string PositionToString(const glm::ivec3& position) const;

	void AddChunkToList(const glm::ivec3& origin);
	void AddOnlyNewChunks(const std::vector<glm::ivec3>& currentOrigins, const std::vector<glm::ivec3>& previousOrigins);
	void RemoveExcludedChunks(const std::vector<glm::ivec3>& oldOrigins);
	void RenderChunksAround(const glm::ivec3& normalizedOrigin);

public:
	explicit ChunkRenderer(WorldGenerator& generator, std::unique_ptr<RenderView>& renderView, Camera& camera);

	void Update();
	void SetRenderView(std::unique_ptr<RenderView>& renderView);
};


