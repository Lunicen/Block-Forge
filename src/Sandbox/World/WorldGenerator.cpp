#include "WorldGenerator.h"

#include "Sandbox/Utils/World/ChunkUtils.h"

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

void WorldGenerator::OptimizeChunk(ChunkData& data, const std::vector<std::vector<std::vector<float>>>& noiseOfChunkWithBorders)
{
	const auto& chunkSize = data.blocks.size();
	
	for (size_t x = 0; x < chunkSize; ++x)
	{
		for (size_t y = 0; y < chunkSize; ++y)
		{
			for (size_t z = 0; z < chunkSize; ++z)
			{
				OptimizeChunkAt(static_cast<int>(x) + 1, static_cast<int>(y) + 1, static_cast<int>(z) + 1, 
								data, noiseOfChunkWithBorders);
			}
		}
	}
}

WorldGenerator::WorldGenerator(const int seed, Shader& blockShader) : _seed(seed)
{
	auto biomeProvider = BiomeProvider("src/Data/Biomes.json", blockShader);

	_biomes = biomeProvider.GetBiomes(_seed);
	const auto placerNoise = biomeProvider.GetPlacerNoise(_seed);

	_placer = std::make_unique<BiomePlacer>(placerNoise, _biomes);
}

void WorldGenerator::PaintChunk(ChunkData& chunk, const glm::ivec3 origin, const int size) const
{
	_placer->PaintChunk(origin, chunk, size);
	//const auto noiseOfChunkWithBorders = _placer->GetChunkNoiseWithBorders(origin, size);
	
	//OptimizeChunk(chunk, noiseOfChunkWithBorders);
}

bool WorldGenerator::IsInitialized() const
{
	return _biomes.empty() ? false : true;
}
