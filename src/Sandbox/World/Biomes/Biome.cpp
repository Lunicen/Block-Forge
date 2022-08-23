#include "Biome.h"

#include "Sandbox/Utils/ChunkUtils.h"

void Biome::SetDataAccordingToNoise(ChunkData& data, const int x, const int y, const int z, float xBlock, float yBlock, float zBlock, const float noise) const
{
	if (noise > 0)
	{
		data.blocks[x][y][z] = nullptr;
		data.isBlockVisibleAt[x][y][z] = false;
	}
	else
	{
		data.blocks[x][y][z] = std::make_unique<Block>(xBlock, yBlock, zBlock, _blockShader);
		data.isBlockVisibleAt[x][y][z] = true;
	}
}

Biome::Biome(std::string name, Noise noise, Shader& blockShader) : _name(std::move(name)), _noise(std::move(noise)), _blockShader(blockShader)
{
}

void Biome::PaintChunk(const glm::ivec3 origin, ChunkData& data, const int size) const
{
	const auto noise = _noise.GetChunkNoise(origin, size);
	const auto midPoint = ChunkUtils::CalculateMidPoint(size);

	const auto xBlock = static_cast<float>(origin.x) * static_cast<float>(size) - midPoint;
	const auto yBlock = static_cast<float>(origin.y) * static_cast<float>(size) - midPoint;
	const auto zBlock = static_cast<float>(origin.z) * static_cast<float>(size) - midPoint;

	for (auto x = 0; x < size; ++x)
	{
		for (auto y = 0; y < size; ++y)
		{
			for (auto z = 0; z < size; ++z)
			{
				SetDataAccordingToNoise(
					data,
					x, y, z,
					static_cast<float>(x) + xBlock, static_cast<float>(y) + yBlock, static_cast<float>(z) + zBlock, 
					noise[x][y][z]
				);
			}
		}
	}
}

std::vector<std::vector<std::vector<float>>> Biome::GetChunkNoise(const glm::ivec3 origin, const int size) const
{
	return _noise.GetChunkNoise(origin, size);
}

std::vector<std::vector<std::vector<float>>> Biome::GetChunkNoiseWithBorders(const glm::ivec3 origin, const int size) const
{
	return _noise.GetChunkNoiseWithBorders(origin, size);
}
