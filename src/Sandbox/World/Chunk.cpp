#include "Chunk.h"

Chunk::Chunk(const glm::vec3 origin, ChunkManager& chunkManager) : _chunkManager(chunkManager)
{
	_midPoint = static_cast<float>(chunk_size) / 2.0f;
	_midPoint += chunk_size % 2 == 0 ? 0.5f : 0.0f;

	_origin = origin * static_cast<float>(chunk_size);
}

void Chunk::Init()
{
	const auto xBlock = _origin.x - _midPoint;
	const auto yBlock = _origin.y - _midPoint;
	const auto zBlock = _origin.z - _midPoint;

	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				_blocks[x][y][z] = std::make_unique<Block>(static_cast<float>(x) + xBlock, 
														   static_cast<float>(y) + yBlock,
								                           static_cast<float>(z) + zBlock,
								                           _chunkManager.GetBlockShader());
			}
		}
	}
}

void Chunk::Draw() const
{
	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				_chunkManager.GetCamera().Add(*_blocks[x][y][z]);
				_blocks[x][y][z]->Draw();
			}
		}
	}
}
