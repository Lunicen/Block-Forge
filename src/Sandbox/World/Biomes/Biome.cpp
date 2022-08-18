#include "Biome.h"

Biome::Biome(std::string name, Noise noise, Shader& block) : _name(std::move(name)), _noise(std::move(noise)), _blockShader(block)
{
}

void Biome::PaintChunk(Chunk& chunk, const int chunkSize)
{
	const auto noise = _noise.GetChunkNoise(chunk.GetOrigin(), chunkSize);
	const auto origin = chunk.GetOrigin();
	const auto midPoint = chunk.GetMidpoint();

	std::vector<std::vector<std::vector<Block*>>> blocks;
	const auto xBlock = origin.x - midPoint;
	const auto yBlock = origin.y - midPoint;
	const auto zBlock = origin.z - midPoint;

	auto index = 0;

	blocks.reserve(chunkSize);
	for (auto x = 0; x < chunkSize; ++x)
	{
		blocks[x].reserve(chunkSize);
		for (auto y = 0; y < chunkSize; ++y)
		{
			blocks[x][y].reserve(chunkSize);
			for (auto z = 0; z < chunkSize; ++z)
			{
				blocks[x][y][z] = noise[index++] > 0 ? nullptr : new Block(static_cast<float>(x) + xBlock, 
																		   static_cast<float>(y) + yBlock,
												                           static_cast<float>(z) + zBlock,
												                           _blockShader);
			}
		}
	}

	chunk.Load(blocks);
	chunk.Optimize();
}
