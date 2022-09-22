#include "WorldGenerator.h"

#include "Biomes/Biome.h"

void WorldGenerator::OptimizeBlock(const Position& origin, BlockVisibility& block, const std::vector<std::vector<std::vector<float>>>& surroundingNoise)
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

	const int& x = static_cast<int>(factor.x) + static_cast<int>(origin.x) + 1;
	const int& y = static_cast<int>(factor.y) + static_cast<int>(origin.y) + 1;
	const int& z = static_cast<int>(factor.z) + static_cast<int>(origin.z) + 1;

	block.visibility = {false, false, false, false, false, false};

	if (noise[x + 1][y][z] > 0) block.visibility.right  = true;
	if (noise[x - 1][y][z] > 0) block.visibility.left   = true;

	if (noise[x][y + 1][z] > 0) block.visibility.top    = true;
	if (noise[x][y - 1][z] > 0) block.visibility.bottom = true;

	if (noise[x][y][z + 1] > 0) block.visibility.back   = true;
	if (noise[x][y][z - 1] > 0) block.visibility.front  = true;
}

void WorldGenerator::OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto noise = _placer->GetChunkNoise(frame, 1);
	
	for (auto& block : blocks.block)
	{
		OptimizeBlock(block.first, block.second, noise);
	}
}

WorldGenerator::WorldGenerator(const int seed) : _blocksMap("src/Data/Blocks.json"), _seed(seed)
{
	auto biomeProvider = BiomeProvider("src/Data/Biomes.json", _blocksMap);
	_biomes = biomeProvider.GetBiomes(_seed);

	const auto placerNoise = biomeProvider.GetPlacerNoise(_seed);
	_placer = std::make_unique<BiomePlacer>(placerNoise, _biomes);
}

void WorldGenerator::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	_placer->PaintChunk(frame, blocks);
	OptimizeChunk(frame, blocks);
}
