#include "Chunk.h"

void Chunk::IterateThroughChunkAnd(const Action actionToDo)
{
	const auto xBlock = _origin.x - _midPoint;
	const auto yBlock = _origin.y - _midPoint;
	const auto zBlock = _origin.z + _zMidPoint;

	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				switch (actionToDo)
				{
					case Action::allocateBlocks: 
						_blocks[x][y][z] = new Block(static_cast<float>(x) + xBlock, 
													 static_cast<float>(y) + yBlock,
						                             static_cast<float>(z) + zBlock, _blockShader);
						break;

					case Action::drawChunk: 
						_camera.Add(_blocks[x][y][z]);
						_blocks[x][y][z]->Draw();
						break;

					case Action::deallocateBlocks: 
						delete _blocks[x][y][z];
						break;
				}
			}
		}
	}
}

Chunk::Chunk(const glm::vec3 origin, Shader& blockShader, Camera& camera) : _blockShader(blockShader), _camera(camera)
{
	_midPoint = static_cast<float>(chunk_size) / 2.0f;
	_midPoint += (chunk_size % 2 == 0) ? 0.5f : 0.0f;

	_zMidPoint = 1.5f - floorf((chunk_size - 1) / 2.0f);

	_origin = origin * static_cast<float>(chunk_size);
}

void Chunk::Load()
{
	IterateThroughChunkAnd(Action::allocateBlocks);
}

void Chunk::Draw()
{
	IterateThroughChunkAnd(Action::drawChunk);
}

void Chunk::Unload()
{
	IterateThroughChunkAnd(Action::deallocateBlocks);
}
