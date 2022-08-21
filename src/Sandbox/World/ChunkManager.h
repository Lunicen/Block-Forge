#pragma once
#include <vector>

#include "Sandbox/Camera.h"
#include "Chunk.h"
#include "WorldGenerator.h"
class Chunk; // Forward declaration

/// @class ChunkManager
/// @brief Handles managing the chunks around the camera.
///	@details This class handles @ref Chunk objects and manages them for optimal experience.
class ChunkManager
{
	Log& _log = Log::Get();
	
	Camera& _camera;
	std::vector<std::unique_ptr<Chunk>> _loadedChunks = {};
	glm::vec3 _lastChunkWithPlayer{};

	int _renderDistance;
	int _chunkSize;
	unsigned _chunksToRender;
	std::unique_ptr<WorldGenerator> _generator = nullptr;

	glm::vec3 GetNormalizedPosition(glm::vec3 position) const;
	static unsigned CountChunksRecursive(unsigned level);
	
	void ClearChunksQueue();
	void UpdateChunksContainer(glm::vec3 position);

public:

	/// @brief The constructor.
	///	@param chunkSize - the size of the generated chunks
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param camera - the object around which the chunks are rendered.
	ChunkManager(int chunkSize, int renderDistance, Camera& camera);

	/// @brief Updates the chunk manager too adapt to the current frame.
	void Update();

	void Bind(std::unique_ptr<WorldGenerator>& worldGenerator);

	/// @brief Returns the amount of chunks that could be generated on the current render distance settings.
	unsigned GetChunksToRenderCount() const;

	Camera& GetCamera() const;

	unsigned GetChunkSize() const;
};

