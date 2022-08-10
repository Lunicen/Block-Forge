#include "Chunk.h"

void Chunk::IterateThroughChunkAnd(const Action actionToDo)
{
	const auto xBlock = static_cast<int>(_origin.x);
	const auto yBlock = static_cast<int>(_origin.y);
	const auto zBlock = static_cast<int>(_origin.z);

	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				switch (actionToDo)
				{
					case Action::allocateBlocks: 
						_blocks[x][y][z] = new Block(x + xBlock, y + yBlock, z + zBlock, _blockShader);
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
