#pragma once
#include <vector>

#include "Chunk.h"

/// @class ChunkManager
/// @brief Handles managing the chunks around the camera.
///	@details This class handles @see Chunk objects and manages them for optimal experience.
class ChunkManager
{
	Log& _log = Log::Get();

	Camera& _camera;
	int _renderDistance;
	unsigned _chunksToRender;
	glm::vec3 _lastPosition{};

	std::vector<Chunk*> _loadedChunks = {};
	static unsigned CountChunksRecursive(unsigned level);
	void UpdateChunksContainer(glm::vec3 position);

	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

public:

	/// @brief The constructor.
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param camera - the object around which the chunks are rendered.
	ChunkManager(int renderDistance, Camera& camera);

	/// @brief Updates the chunk manager to adapt to the current frame.
	void Update() const;

	/// @brief Returns the amount of chunks that could be generated on the current render distance settings.
	unsigned GetChunksToRenderCount() const;
};

