#include "WorldGenerator.h"

void WorldGenerator::PrepareForPainting(std::vector<std::vector<std::vector<Block*>>>& blocks, const int vectorSize)
{
	blocks.resize(vectorSize);
	for (auto x = 0; x < vectorSize; ++x)
	{
		blocks[x].resize(vectorSize);
		for (auto y = 0; y < vectorSize; ++y)
		{
			blocks[x][y].resize(vectorSize);
		}
	}
}

WorldGenerator::WorldGenerator(const int seed) : _seed(seed)
{
}

void WorldGenerator::Initialize(Shader& blockShader)
{
	auto biomeProvider = BiomeProvider("src/Data/Biomes.json", blockShader);
	_biomes = biomeProvider.GetBiomes(_seed);
}

std::vector<std::vector<std::vector<Block*>>> WorldGenerator::GetPaintedChunkWithBorders(const glm::ivec3 chunkOrigin, const int chunkSize) const
{
	auto blocks = std::vector<std::vector<std::vector<Block*>>>();
	const auto chunkSizeWithBorders = chunkSize + 2;
	const auto origin = chunkOrigin - glm::ivec3(1, 1, 1);

	PrepareForPainting(blocks, chunkSizeWithBorders);

	_biomes.at(0).PaintChunk(blocks, origin, chunkSizeWithBorders);

	return blocks;
}

bool WorldGenerator::IsInitialized() const
{
	return _biomes.empty() ? false : true;
}
