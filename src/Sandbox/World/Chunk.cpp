#include "Chunk.h"

void Chunk::DrawBlockIfExists(const int x, const int y, const int z) const
{
	if (_blocks[x][y][z] != nullptr && _isVisible[x][y][z])
	{
		_chunkManager.GetCamera().Add(*_blocks[x][y][z]);
		_blocks[x][y][z]->Draw();
	}
}

/*void Chunk::AddBlockToMatrixWithOptimization(const int x, const int y, const int z,
	const std::vector<std::vector<std::vector<Block*>>>& blocks)
{
	_blocks[x - 1][y - 1][z - 1] = blocks[x][y][z];
	
	if (blocks[x - 1][y][z] == nullptr || blocks[x + 1][y][z] == nullptr ||
		blocks[x][y - 1][z] == nullptr || blocks[x][y + 1][z] == nullptr ||
		blocks[x][y][z - 1] == nullptr || blocks[x][y][z + 1] == nullptr)
	{
		_isVisible[x - 1][y - 1][z - 1] = false;
	}
	else
	{
		_isVisible[x - 1][y - 1][z - 1] = true;
	}
}

void Chunk::LoadAndOptimize(const std::vector<std::vector<std::vector<Block*>>>& blocks)
{
	const auto chunkSize = static_cast<int>(_chunkManager.GetChunkSize());

	for (auto x = 0; x < chunkSize; ++x)
	{
		for (auto y = 0; y < chunkSize; ++y)
		{
			for (auto z = 0; z < chunkSize; ++z)
			{
				AddBlockToMatrixWithOptimization(x + 1, y + 1, z + 1, blocks);
			}
		}
	}
}*/

Chunk::Chunk(const glm::ivec3 origin, ChunkManager& chunkManager) : _chunkManager(chunkManager)
{
	const auto chunkSize = static_cast<int>(_chunkManager.GetChunkSize());

	_origin = origin * chunkSize;
}

void Chunk::Load(ChunkData& chunkData)
{
	_blocks = std::move(chunkData.blocks);
	_isVisible = std::move(chunkData.visibilityFlag);
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
