#include "Biome.h"

#include "Sandbox/Utils/ChunkUtils.h"

Biome::Biome(std::string name, Noise noise, Shader& blockShader) : _name(std::move(name)), _noise(std::move(noise)), _blockShader(blockShader)
{
}

void Biome::PaintColumn(std::vector<std::vector<std::vector<Block*>>>& blocks, const glm::vec3 origin, const int chunkSize, const int offsetX, const int offsetY, const int offsetZ) const
{
	const auto noise = _noise.GetColumnNoise(origin, chunkSize, offsetX, offsetY, offsetZ);
	const auto midPoint = ChunkUtils::CalculateMidPoint(chunkSize);
	auto index = 0;

	const auto xBlock = origin.x - midPoint;
	const auto yBlock = origin.y - midPoint;
	const auto zBlock = origin.z - midPoint;
	
	for (auto y = 0; y < chunkSize; ++y)
	{
		blocks[offsetX][y][offsetZ] = noise[index++] <= 0 ? nullptr : new Block(static_cast<float>(offsetX) + xBlock, 
																			   static_cast<float>(y)	   + yBlock,
																			   static_cast<float>(offsetZ) + zBlock,
																			   _blockShader);
	}
}

void Biome::PaintChunk(std::vector<std::vector<std::vector<Block*>>>& blocks, const glm::vec3 origin, const int chunkSize) const
{
	const auto noise = _noise.GetChunkNoise(origin, chunkSize);
	const auto midPoint = ChunkUtils::CalculateMidPoint(chunkSize);
	
	const auto xBlock = origin.x - midPoint;
	const auto yBlock = origin.y - midPoint;
	const auto zBlock = origin.z - midPoint;

	auto index = 0;
	
	for (auto x = 0; x < chunkSize; ++x)
	{
		for (auto y = 0; y < chunkSize; ++y)
		{
			for (auto z = 0; z < chunkSize; ++z)
			{
				blocks[x][y][z] = noise[index++] <= 0 ? nullptr : new Block(static_cast<float>(x) + xBlock, 
																		   static_cast<float>(y) + yBlock,
												                           static_cast<float>(z) + zBlock,
																		   _blockShader);
			}
		}
	}
}

std::string Biome::GetName() const
{
	return _name;
}
