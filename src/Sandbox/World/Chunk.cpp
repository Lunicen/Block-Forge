#include "Chunk.h"

Chunk::Chunk(const glm::vec3 origin, Shader& blockShader, Camera& camera) : _blockShader(blockShader), _camera(camera)
{
	_midPoint = static_cast<float>(chunk_size) / 2.0f;
	_midPoint += (chunk_size % 2 == 0) ? 0.5f : 0.0f;

	_zMidPoint = 1.5f - floorf((chunk_size - 1) / 2.0f);

	_origin = origin * static_cast<float>(chunk_size);
}

void Chunk::Load()
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
				_blocks[x][y][z] = new Block(static_cast<float>(x) + xBlock, 
											 static_cast<float>(y) + yBlock,
				                             static_cast<float>(z) + zBlock, _blockShader);
			}
		}
	}
}

void Chunk::Draw()
{
	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				_camera.Add(_blocks[x][y][z]);
				_blocks[x][y][z]->Draw();
			}
		}
	}
}

void Chunk::Unload() const
{
	for (int x = 0; x < chunk_size; ++x)
	{
		for (auto y = 0; y < chunk_size; ++y)
		{
			for (auto z = 0; z < chunk_size; ++z)
			{
				delete _blocks[x][y][z];
				break;
			}
		}
	}
}
