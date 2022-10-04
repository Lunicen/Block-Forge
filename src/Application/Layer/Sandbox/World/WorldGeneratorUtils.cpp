#include "WorldGeneratorUtils.h"

void WorldGeneratorUtils::OptimizeBlock(const Position& origin, BlockData& block,
                                        const std::vector<std::vector<std::vector<float>>>& surroundingNoise)
{
	const auto& noise = surroundingNoise;
	const auto frameSize = noise.size() - 2;

	glm::vec3 factor = origin;
	factor /= frameSize;

	factor.x = floor(factor.x);
	factor.y = floor(factor.y);
	factor.z = floor(factor.z);
	
	factor = -factor;
	factor *= frameSize;

	const int& x = static_cast<int>(factor.x) + origin.x + 1;
	const int& y = static_cast<int>(factor.y) + origin.y + 1;
	const int& z = static_cast<int>(factor.z) + origin.z + 1;

	block.blockFlags &= 0b00000011; // Disable all faces

	if (noise[x + 1][y][z] > 0) block.blockFlags |= 0b00010000; // right
	if (noise[x - 1][y][z] > 0) block.blockFlags |= 0b00100000; // left

	if (noise[x][y + 1][z] > 0) block.blockFlags |= 0b00001000; // top
	if (noise[x][y - 1][z] > 0) block.blockFlags |= 0b00000100; // bottom

	if (noise[x][y][z + 1] > 0) block.blockFlags |= 0b01000000; // back
	if (noise[x][y][z - 1] > 0) block.blockFlags |= 0b10000000; // front
}

void WorldGeneratorUtils::OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks, const BiomePlacer& biomePlacer)
{
	const auto noise = biomePlacer.GetChunkNoise(frame, 1);
	
	for (auto& block : blocks)
	{
		OptimizeBlock(block.first, block.second, noise);
	}
}
