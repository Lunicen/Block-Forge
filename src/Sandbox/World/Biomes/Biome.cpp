#include "Biome.h"

void Biome::SetBlockAccordingToNoise(ChunkBlocks& blocks, const glm::ivec3 origin, const float noise) const
{
	if (noise > 0) return;

	const BlockVisibility blockData = 
	{
		_blocksHandler.Get("dirt")
	};

	blocks.block[origin] = blockData;
}

Biome::Biome(std::string name, const Noise3D& noise, BlocksHandler& blocksHandler)
	: Noise3D(noise), _name(std::move(name)), _blocksHandler(blocksHandler)
{
}

void Biome::PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, const int xOffset, const int yOffset, const int zOffset) const
{
	const auto& x = xOffset;
	const auto& z = zOffset;

	const auto noise = GetColumnNoise(frame, xOffset, yOffset, zOffset);
	const auto origin = frame.origin * static_cast<int>(frame.size);

	for (size_t y = 0; y < frame.size; ++y)
	{
		SetBlockAccordingToNoise(
			blocks,
			origin + glm::ivec3(x, y, z),
			noise[y]
		);
	}
}

void Biome::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto noise = GetNoise(frame);
	const auto origin = frame.origin * static_cast<int>(frame.size);

	for (size_t x = 0; x < frame.size; ++x)
	{
		for (size_t y = 0; y < frame.size; ++y)
		{
			for (size_t z = 0; z < frame.size; ++z)
			{
				SetBlockAccordingToNoise(
					blocks,
					origin + glm::ivec3(x, y, z),
					noise[x][y][z]
				);
			}
		}
	}
}