#include "Chunk.h"

void Chunk::DrawBlockIfExists(const int x, const int y, const int z) const
{
	if (_blocks[x][y][z] != nullptr && _isVisible[x][y][z])
	{
		_chunkManager.GetCamera().Add(*_blocks[x][y][z]);
		_blocks[x][y][z]->Draw();
	}
}

Chunk::Chunk(const glm::ivec3 origin, ChunkManager& chunkManager) : _chunkManager(chunkManager)
{
	const auto chunkSize = static_cast<int>(_chunkManager.GetChunkSize());

	_origin = origin * chunkSize;
}

void Chunk::Load(ChunkData& chunkData)
{
	_blocks = std::move(chunkData.blocks);
	_isVisible = std::move(chunkData.isBlockVisibleAt);
}

void Chunk::Draw() const
{
	const auto chunkSize = static_cast<int>(_chunkManager.GetChunkSize());

	for (auto x = 0; x < chunkSize; ++x)
	{
		for (auto y = 0; y < chunkSize; ++y)
		{
			for (auto z = 0; z < chunkSize; ++z)
			{
				DrawBlockIfExists(x, y, z);
			}
		}
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _origin;
}
