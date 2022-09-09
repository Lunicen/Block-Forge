#include "Chunk.h"


void Chunk::DrawBlockIfExists(const size_t& x, const size_t& y, const size_t& z) const
{
	if (_blocks.blockAt[x][y][z] != nullptr && _blocks.isBlockVisibleAt[x][y][z])
	{
		_camera.Bind(*_blocks.blockAt[x][y][z]);
		_blocks.blockAt[x][y][z]->Draw();
	}
}

Chunk::Chunk(const ChunkFrame& frame, ChunkBlocks blocks, Camera& camera)
	: _frame(frame), _blocks(std::move(blocks)), _camera(camera)
{
}

void Chunk::Draw() const
{
	for (size_t x = 0; x < _frame.size; ++x)
	{
		for (size_t y = 0; y < _frame.size; ++y)
		{
			for (size_t z = 0; z < _frame.size; ++z)
			{
				DrawBlockIfExists(x, y, z);
			}
		}
	}
}

glm::ivec3 Chunk::GetOrigin() const
{
	return _frame.origin;
}
