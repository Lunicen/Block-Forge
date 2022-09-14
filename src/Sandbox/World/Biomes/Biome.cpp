#include "Biome.h"
#include "Sandbox/World/Chunk/ChunkUtils.h"

void Biome::SetBlockAccordingToNoise(std::shared_ptr<BlockModel>& block, const glm::ivec3 origin, const float noise) const
{
	if (noise > 0) return;
	
	_blocksQueue.Add(block, origin);
}

Biome::Biome(std::string name, const Noise3D& noise, const std::reference_wrapper<BlocksQueue> blocksQueue) : Noise3D(noise), _name(std::move(name)), _blocksQueue(blocksQueue)
{
}

void Biome::PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, const int xOffset, const int yOffset, const int zOffset) const
{
	const auto& x = xOffset;
	const auto& z = zOffset;

	const auto noise = GetColumnNoise(frame, xOffset, yOffset, zOffset);

	for (size_t y = 0; y < frame.size; ++y)
	{
		SetBlockAccordingToNoise(
			blocks.blockAt[x][y][z],
			glm::ivec3(x, y, z),
			noise[y]
		);
	}
}

void Biome::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto noise = GetNoise(frame);

	for (size_t x = 0; x < frame.size; ++x)
	{
		for (size_t y = 0; y < frame.size; ++y)
		{
			for (size_t z = 0; z < frame.size; ++z)
			{
				SetBlockAccordingToNoise(
					blocks.blockAt[x][y][z],
					glm::ivec3(x, y, z),
					noise[x][y][z]
				);
			}
		}
	}
}