#include "Chunk.h"

void Chunk::IterateThroughChunkAnd(Action actionToDo)
{
	const auto xStart = static_cast<int>(_origin.x);
	const auto yStart = static_cast<int>(_origin.y);
	const auto zStart = static_cast<int>(_origin.z);

	for (int x = xStart; x < chunk_size; ++x)
	{
		for (auto y = yStart; y < chunk_size; ++y)
		{
			for (auto z = zStart; z < chunk_size; ++z)
			{
				switch (actionToDo)
				{
					case Action::allocateBlocks: 
						_blocks[x][y][z] = new Block(x, y, z, _blockShader);
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

Chunk::Chunk(const glm::vec3 origin, Shader& blockShader, Camera& camera) : _origin(origin), _blockShader(blockShader), _camera(camera)
{
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
