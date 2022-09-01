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
	std::vector<glm::ivec3> _loadedChunksOrigin = {};
	glm::ivec3 _lastChunkWithPlayer{};

	int _renderDistance;
	int _chunkSize;
	unsigned _chunksToRender;
	std::shared_ptr<WorldGenerator> _generator{};

	glm::ivec3 GetNormalizedPosition(glm::vec3 position) const;
	static unsigned CountChunksRecursive(unsigned level);
	void RemoveExcludedChunks(const std::vector<glm::ivec3>& oldOrigins);

	ChunkFrame CreateChunkFrame(const glm::ivec3& origin) const;
	ChunkBlocks CreateChunkBlocks() const;

	void AddChunkToListIfIsNew(const glm::ivec3& currentOrigin, const std::vector<glm::ivec3>& oldOrigins);
	void UpdateChunksContainer(glm::ivec3 normalizedPosition);

public:

	/// @brief The constructor.
	///	@param chunkSize - the size of the generated chunks
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param camera - the object around which the chunks are rendered.
	ChunkManager(int chunkSize, int renderDistance, Camera& camera);

	/// @brief Updates the chunk manager to adapt to the current frame.
	void Update();

	/// @brief Binds world generator to the chunk manager.
	///	@details The world generator is used to define how the world is generated, when
	///	this class handles only displaying it in an optimal way.
	///	@param worldGenerator - reference to the world generator.
	void Bind(const std::shared_ptr<WorldGenerator>& worldGenerator);

	/// @brief Get the amount of chunks that could be generated on the current render distance settings.
	unsigned GetChunksToRenderCount() const;

	/// @brief Get the camera object attached to this class.
	Camera& GetCamera() const;

	/// @brief Get the size of chunks that are generated.
	unsigned GetChunkSize() const;
};

