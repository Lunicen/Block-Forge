#include "Biome.h"

#include "Sandbox/Utils/Chunk/ChunkUtils.h"

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

Biome::Biome(std::string name, const Noise3D& noise, Shader& blockShader) : Noise3D(noise), _name(std::move(name)),
                                                                            _blockShader(blockShader)
{
}

void Biome::PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, const int xOffset, const int yOffset, const int zOffset) const
{
	const auto& x = xOffset;
	const auto& z = zOffset;

	const auto noise = GetColumnNoise(frame, xOffset, yOffset, zOffset);
	const auto midPoint = ChunkUtils::CalculateMidPoint(frame.size);

	const auto xBlock = static_cast<float>(frame.origin.x * frame.size) - midPoint;
	const auto yBlock = static_cast<float>(frame.origin.y * frame.size) - midPoint;
	const auto zBlock = static_cast<float>(frame.origin.z * frame.size) - midPoint;

	for (size_t y = 0; y < frame.size; ++y)
	{
		SetBlockAccordingToNoise(
			blocks.blocks[x][y][z],
			static_cast<float>(x) + xBlock, 
			static_cast<float>(y) + yBlock, 
			static_cast<float>(z) + zBlock, 
			noise[y]
		);

		blocks.isBlockVisibleAt[x][y][z] = blocks.blocks[x][y][z] == nullptr ? false : true;
	}
}

void Biome::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto noise = GetNoise(frame);
	const auto midPoint = ChunkUtils::CalculateMidPoint(frame.size);

	const auto xBlock = static_cast<float>(frame.origin.x * frame.size) - midPoint;
	const auto yBlock = static_cast<float>(frame.origin.y * frame.size) - midPoint;
	const auto zBlock = static_cast<float>(frame.origin.z * frame.size) - midPoint;

	for (size_t x = 0; x < frame.size; ++x)
	{
		for (size_t y = 0; y < frame.size; ++y)
		{
			for (size_t z = 0; z < frame.size; ++z)
			{
				SetBlockAccordingToNoise(
					blocks.blocks[x][y][z],
					static_cast<float>(x) + xBlock, 
					static_cast<float>(y) + yBlock, 
					static_cast<float>(z) + zBlock, 
					noise[x][y][z]
				);

				blocks.isBlockVisibleAt[x][y][z] = blocks.blocks[x][y][z] == nullptr ? false : true;
			}
		}
	}
}