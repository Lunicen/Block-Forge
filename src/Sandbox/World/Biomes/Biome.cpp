#include "Biome.h"

#include "Sandbox/Utils/ChunkUtils.h"

void Biome::SetBlockAccordingToNoise(std::unique_ptr<Block>& block, float x, float y, float z, const float noise) const
{
	block = noise > 0 ? std::make_unique<Block>(x, y, z, _blockShader) : nullptr;
}

Biome::Biome(std::string name, Noise noise, Shader& blockShader) : _name(std::move(name)), _noise(std::move(noise)), _blockShader(blockShader)
{
}

void Biome::PaintColumn(const glm::ivec3 origin, ChunkData& data, const int chunkSize, const int offsetX, const int offsetY, const int offsetZ) const
{
	const auto noise = _noise.GetColumnNoise(origin, chunkSize, offsetX, offsetY, offsetZ);
	const auto midPoint = ChunkUtils::CalculateMidPoint(chunkSize);
	auto index = 0;

	const auto xBlock = static_cast<float>(origin.x) - midPoint;
	const auto yBlock = static_cast<float>(origin.y) - midPoint;
	const auto zBlock = static_cast<float>(origin.z) - midPoint;

	for (auto y = 0; y < chunkSize; ++y)
	{
		SetBlockAccordingToNoise(data.blocks[offsetX][y][offsetZ], 
									 static_cast<float>(offsetX) + xBlock, 
									 static_cast<float>(y) + yBlock,
									 static_cast<float>(offsetZ) + zBlock,
									 noise[index++]);
	}
}

void Biome::PaintChunk(const glm::ivec3 origin, ChunkData& data, const int size) const
{
	const auto noise = _noise.GetChunkNoise(origin, size);
	const auto midPoint = ChunkUtils::CalculateMidPoint(size);

	const auto xBlock = static_cast<float>(origin.x) - midPoint;
	const auto yBlock = static_cast<float>(origin.y) - midPoint;
	const auto zBlock = static_cast<float>(origin.z) - midPoint;

	auto index = 0;
	
	for (auto x = 0; x < size; ++x)
	{
		for (auto y = 0; y < size; ++y)
		{
			for (auto z = 0; z < size; ++z)
			{
				SetBlockAccordingToNoise(data.blocks[x][y][z], 
										 static_cast<float>(x) + xBlock, 
										 static_cast<float>(y) + yBlock,
										 static_cast<float>(z) + zBlock,
										 noise[index++]);
			}
		}
	}
}

std::string Biome::GetName() const
{
	return _name;
}

std::vector<float> Biome::GetColumnNoise(const glm::ivec3 origin, const int chunkSize, const int offsetX, const int offsetY, const int offsetZ) const
{
	return _noise.GetColumnNoise(origin, chunkSize, offsetX, offsetY, offsetZ);
}

std::vector<float> Biome::GetChunkNoise(const glm::ivec3 origin, const int chunkSize) const
{
	return _noise.GetChunkNoise(origin, chunkSize);
}
