#include "WorldGenerator.h"

#include "Sandbox/Utils/ChunkUtils.h"

void WorldGenerator::OptimizeChunkAt(const int x, const int y, const int z, ChunkData& data, const std::vector<std::vector<std::vector<float>>>& surroundingNoise)
{
	const auto& noise = surroundingNoise;

	// If it's air
	if (noise[x][y][z] > 0)
	{
		data.isBlockVisibleAt[x - 1][y - 1][z - 1] = false;
		return;
	}

	// If it's not completely surrounded by blocks, it can be visible to the Camera
	if (noise[x - 1][y][z] > 0 || noise[x + 1][y][z] > 0 || 
		noise[x][y - 1][z] > 0 || noise[x][y + 1][z] > 0 || 
		noise[x][y][z - 1] > 0 || noise[x][y][z + 1] > 0)
	{
		data.isBlockVisibleAt[x - 1][y - 1][z - 1] = true;
	}
	else
	{
		data.isBlockVisibleAt[x - 1][y - 1][z - 1] = false;
	}
}

void WorldGenerator::OptimizeChunk(ChunkData& data, const std::vector<float>& noiseOfChunkWithBorders)
{
	const auto& chunkSize = data.blocks.size();
	const auto chunkifiedNoise = ChunkUtils::Chunkify(noiseOfChunkWithBorders, static_cast<int>(chunkSize) + 2);

	for (size_t x = 0; x < chunkSize; ++x)
	{
		for (size_t y = 0; y < chunkSize; ++y)
		{
			for (size_t z = 0; z < chunkSize; ++z)
			{
				OptimizeChunkAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1, static_cast<int>(z) + 1, 
								data, chunkifiedNoise);
			}
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

void WorldGenerator::PaintChunk(ChunkData& chunk, const glm::ivec3 origin, const int size) const
{
	const auto selectedBiome = _biomes.at(0);
	selectedBiome.PaintChunk(origin, chunk, size);

	const auto noiseOfChunkWithBorders = selectedBiome.GetChunkNoiseWithBorders(origin, size);

	OptimizeChunk(chunk, noiseOfChunkWithBorders);
}

bool WorldGenerator::IsInitialized() const
{
	return _biomes.empty() ? false : true;
}