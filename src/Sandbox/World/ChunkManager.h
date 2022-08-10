#pragma once
#include <vector>

#include "Chunk.h"

class ChunkManager
{
	Log& _log = Log::Get();

	Camera& _camera;
	unsigned _distance;

	std::vector<Chunk*> _loadedChunks = {};
	static unsigned CountChunksRecursive(unsigned level);

public:
	ChunkManager(unsigned renderDistance, Camera& camera);
	void Update();

	unsigned GetChunksToRenderCount() const;
};

