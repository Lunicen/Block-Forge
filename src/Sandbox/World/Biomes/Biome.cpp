#include "Biome.h"

#include "Sandbox/Utils/World/ChunkUtils.h"

void Biome::SetBlockAccordingToNoise(std::unique_ptr<Block>& block, float xBlock, float yBlock, float zBlock, const float noise) const
{
	if (noise > 0)
	{
		block = nullptr;
	}
	else
	{
		block = std::make_unique<Block>(xBlock, yBlock, zBlock, _blockShader);
	}
}

Biome::Biome(std::string name, Noise3D noise, Shader& blockShader) : _name(std::move(name)),
                                                                     _noise(std::move(noise)),
                                                                     _blockShader(blockShader)
{
}

void Biome::PaintColumn(const glm::ivec3 origin, ChunkData& data, const int size, const int xOffset, const int yOffset, const int zOffset) const
{
	const auto& x = xOffset;
	const auto& z = zOffset;

	const auto noise = _noise.GetColumnNoise(origin, size, xOffset, yOffset, zOffset);
	const auto midPoint = ChunkUtils::CalculateMidPoint(size);

	const auto xBlock = static_cast<float>(origin.x) * static_cast<float>(size) - midPoint;
	const auto yBlock = static_cast<float>(origin.y) * static_cast<float>(size) - midPoint;
	const auto zBlock = static_cast<float>(origin.z) * static_cast<float>(size) - midPoint;

	for (auto y = 0; y < size; ++y)
	{
		SetBlockAccordingToNoise(
			data.blocks[x][y][z],
			static_cast<float>(x) + xBlock, static_cast<float>(y) + yBlock, static_cast<float>(z) + zBlock, 
			noise[y]
		);

		data.isBlockVisibleAt[x][y][z] = data.blocks[x][y][z] == nullptr ? false : true;
	}
}

void Biome::PaintChunk(const glm::ivec3 origin, ChunkData& data, const int size) const
{
	const auto noise = _noise.GetNoise(origin, size);
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
				SetBlockAccordingToNoise(
					data.blocks[x][y][z],
					static_cast<float>(x) + xBlock, static_cast<float>(y) + yBlock, static_cast<float>(z) + zBlock, 
					noise[x][y][z]
				);

				data.isBlockVisibleAt[x][y][z] = data.blocks[x][y][z] == nullptr ? false : true;
			}
		}
	}
}

std::vector<float> Biome::GetColumnNoise(
	const glm::ivec3 origin, const int size, const int xOffset, const int yOffset, const int zOffset) const
{
	return _noise.GetColumnNoise(origin, size, xOffset, yOffset, zOffset);
}

std::vector<std::vector<std::vector<float>>> Biome::GetNoiseWithBorders(const glm::ivec3 origin, const int size) const
{
	return _noise.GetNoiseWithBorders(origin, size);
}
