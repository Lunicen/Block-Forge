#include "ChunkManager.h"

unsigned ChunkManager::CountChunksRecursive(const unsigned level)
{
	const auto result = 4 * level;

	if (result == 0) return 1;
	return result + CountChunksRecursive(level - 1);
}

ChunkManager::ChunkManager(const unsigned renderDistance, Camera& camera) : _camera(camera), _distance(renderDistance)
{
	_log.Debug("Chunks to render: " + std::to_string(GetChunksToRenderCount()));
}

void ChunkManager::Update()
{
	auto playerPosition = _camera.GetPosition();
}

unsigned ChunkManager::GetChunksToRenderCount() const
{
	unsigned result = 0;
	for (size_t i = 0; i < _distance; ++i)
	{
		result += 2 * CountChunksRecursive(i);
	}

	return CountChunksRecursive(_distance) + result; 
}
