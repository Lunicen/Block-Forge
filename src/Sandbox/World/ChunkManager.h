#pragma once
#include <vector>

#include "Chunk.h"

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
	ChunkManager(int renderDistance, Camera& camera);
	void Update() const;

	unsigned GetChunksToRenderCount() const;
};

