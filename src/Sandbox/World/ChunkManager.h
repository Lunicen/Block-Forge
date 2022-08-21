#pragma once
#include <vector>

#include "Chunk.h"

/// @class ChunkManager
/// @brief Handles managing the chunks around the camera.
///	@details This class handles @see Chunk objects and manages them for optimal experience.
class ChunkManager
{
	Log& _log = Log::Get();
	//Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	Shader& _blockShader;
	Texture& _texture;

	Camera& _camera;
	std::vector<std::unique_ptr<Chunk>> _loadedChunks = {};
	glm::vec3 _lastChunkWithPlayer{};
	int _renderDistance;
	unsigned _chunksToRender;

	glm::vec3 GetNormalizedPosition(glm::vec3 position) const;
	static unsigned CountChunksRecursive(unsigned level);
	void UpdateChunksContainer(glm::vec3 position);

public:

	/// @brief The constructor.
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param camera - the object around which the chunks are rendered.
	///	@param blockShader - shader that will be used for the blocks inside the chunk.
	ChunkManager(int renderDistance, Camera& camera, Shader& blockShader, Texture& texture);

	/// @brief Updates the chunk manager too adapt to the current frame.
	void Update();

	/// @brief Returns the amount of chunks that could be generated on the current render distance settings.
	unsigned GetChunksToRenderCount() const;
};

