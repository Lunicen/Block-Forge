#include "ChunkManager.h"

unsigned ChunkManager::CountChunksRecursive(const unsigned level)
{
	const auto result = 4 * level;

	if (result == 0) return 1;
	return result + CountChunksRecursive(level - 1);
}

void ChunkManager::UpdateChunksContainer(const glm::vec3 position)
{
	for (auto y = -_renderDistance; y <= _renderDistance; ++y)
	{
		const auto xLimiter = _renderDistance - abs(y);
		for (auto x = -xLimiter; x <= xLimiter; ++x)
		{
			const auto zLimiter = abs(abs(x) + abs(y) - _renderDistance);
			for (auto z = -zLimiter; z <= zLimiter; ++z)
			{
				constexpr auto offset = chunk_size / 2;
				const auto chunkPosition = glm::vec3(x + static_cast<int>((position.x + offset) / chunk_size),
				                                     y + static_cast<int>((position.y + offset) / chunk_size),
				                                     z + static_cast<int>((position.z + offset) / chunk_size));
				_log.Trace("Added chunk: " + std::to_string(chunkPosition.x) + ", " + std::to_string(chunkPosition.y) + ", " + std::to_string(chunkPosition.z));

				auto chunk = new Chunk(chunkPosition, _blockShader, _camera);
				chunk->Load();

				_loadedChunks.push_back(chunk);
			}
		}
	}
}

ChunkManager::ChunkManager(const int renderDistance, Camera& camera) : _camera(camera),
                                                                       _renderDistance(renderDistance),
                                                                       _lastPosition(_camera.GetPosition())
{
	_chunksToRender = GetChunksToRenderCount();
	UpdateChunksContainer(_lastPosition);
}

void ChunkManager::Update() const
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
