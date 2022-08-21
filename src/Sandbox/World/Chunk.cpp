#include "Chunk.h"

void Chunk::DrawBlockIfExists(const int x, const int y, const int z) const
{
	if (_blocks[x][y][z] != nullptr && !_isDisabled[x][y][z])
	{
		_chunkManager.GetCamera().Add(*_blocks[x][y][z]);
		_blocks[x][y][z]->Draw();
	}
}

void Chunk::AddBlockToMatrixWithOptimization(const int x, const int y, const int z,
	const std::vector<std::vector<std::vector<Block*>>>& blocks)
{
	if (_blocks[x][y][z] != nullptr)
	{
		delete _blocks[x][y][z];
	}
	
	if (blocks[x - 1][y][z] == nullptr || blocks[x + 1][y][z] == nullptr ||
		blocks[x][y - 1][z] == nullptr || blocks[x][y + 1][z] == nullptr ||
		blocks[x][y][z - 1] == nullptr || blocks[x][y][z + 1] == nullptr)
	{
		_blocks[x][y][z] = blocks[x][y][z];
	}
	else
	{
		_blocks[x][y][z] = nullptr;
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
				AddBlockToMatrixWithOptimization(x, y, z, blocks);
			}
		}
	}
}

Chunk::Chunk(const glm::ivec3 origin, ChunkManager& chunkManager) : _chunkManager(chunkManager)
{
	_origin = origin * static_cast<int>(_chunkManager.GetChunkSize());
}

void Chunk::Load(const std::vector<std::vector<std::vector<Block*>>>& blocks)
{
	if (blocks.size() == _chunkManager.GetChunkSize())
	{
		std::move(blocks.begin(), blocks.end(), std::back_inserter(_blocks));
	}
	else
	{
		LoadAndOptimize(blocks);	
	}
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

Chunk::~Chunk()
{
	for (size_t x = 0; x < _blocks.size(); ++x)
	{
		for (size_t y = 0; y < _blocks[x].size(); ++y)
		{
			for (size_t z = 0; z < _blocks[x][y].size(); ++z)
			{
				delete _blocks[x][y][z];
			}
		}
	}
}
