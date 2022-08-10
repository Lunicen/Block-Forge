#include "ChunkManager.h"

unsigned ChunkManager::CountChunksRecursive(const unsigned level)
{
	const auto result = 4 * level;

	if (result == 0) return 1;
	return result + CountChunksRecursive(level - 1);
}

void ChunkManager::UpdateChunksContainer(glm::vec3 position)
{
	for (auto y = -_renderDistance; y <= _renderDistance; ++y)
	{
		const auto xLimiter = _renderDistance - abs(y);
		for (auto x = -xLimiter; x <= xLimiter; ++x)
		{
			const auto zLimiter = abs(abs(x) + abs(y) - _renderDistance);
			for (auto z = -zLimiter; z <= zLimiter; ++z)
			{
				_log.Trace("Added chunk: " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));

				auto chunk = new Chunk(glm::vec3(x, y, z), _blockShader, _camera);
				chunk->Load();

				_loadedChunks.push_back(chunk);
			}
		}
	}
}

ChunkManager::ChunkManager(const int renderDistance, Camera& camera) : _camera(camera),
                                                                       _renderDistance(renderDistance),
                                                                       _lastPosition(glm::vec3(0, 0, 0))
{
	_chunksToRender = GetChunksToRenderCount();
	UpdateChunksContainer(_lastPosition);
}

void ChunkManager::Update()
{
	for (const auto& chunk : _loadedChunks)
	{
		chunk->Draw();
	}
}

unsigned ChunkManager::GetChunksToRenderCount() const
{
	unsigned result = 0;
	for (auto i = 0; i < _renderDistance; ++i)
	{
		result += 2 * CountChunksRecursive(i);
	}

	return CountChunksRecursive(_renderDistance) + result; 
}
