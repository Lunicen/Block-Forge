#include "WorldGenerator.h"

/*void WorldGenerator::OptimizeChunkAt(const int x, const int y, const int z, ChunkBlocks& blocks, const std::vector<std::vector<std::vector<float>>>& surroundingNoise)
{
	const auto& noise = surroundingNoise;

	// If it's air
	if (noise[x][y][z] > 0)
	{
		blocks.isBlockVisibleAt[x - 1][y - 1][z - 1] = false;
		return;
	}

	// If it's not completely surrounded by blockAt, it can be visible to the Camera
	if (noise[x - 1][y][z] > 0 || noise[x + 1][y][z] > 0 || 
		noise[x][y - 1][z] > 0 || noise[x][y + 1][z] > 0 || 
		noise[x][y][z - 1] > 0 || noise[x][y][z + 1] > 0)
	{
		blocks.isBlockVisibleAt[x - 1][y - 1][z - 1] = true;
	}
	else
	{
		blocks.isBlockVisibleAt[x - 1][y - 1][z - 1] = false;
	}
}

void WorldGenerator::OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto noise = _placer->GetChunkNoise(frame, 1);
	const auto& chunkSize = blocks.blockAt.size();
	
	for (size_t x = 0; x < chunkSize; ++x)
	{
		for (size_t y = 0; y < chunkSize; ++y)
		{
			for (size_t z = 0; z < chunkSize; ++z)
			{
				OptimizeChunkAt(
					static_cast<int>(x) + 1, 
					static_cast<int>(y) + 1, 
					static_cast<int>(z) + 1, 
					blocks, noise);
			}
		}
	}
}*/

WorldGenerator::WorldGenerator(const int seed) : _seed(seed)
{
	auto biomeProvider = BiomeProvider("src/Data/Biomes.json", _blocksQueue);
	_biomes = biomeProvider.GetBiomes(_seed);

	const auto placerNoise = biomeProvider.GetPlacerNoise(_seed);
	_placer = std::make_unique<BiomePlacer>(placerNoise, _biomes);

	auto blocksProvider = BlocksProvider("src/Data/Blocks.json");
	_blockTypes = blocksProvider.GetBlocks();
}

void WorldGenerator::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	_placer->PaintChunk(frame, blocks);
	//OptimizeChunk(frame, blocks);
}
