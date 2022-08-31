#include "BiomePlacer.h"

#include "Sandbox/Utils/World/ChunkUtils.h"

bool BiomePlacer::HasChunkOnlySingleBiome(const std::vector<std::vector<float>>& biomesMap)
{
	const auto& size = biomesMap.size() - 1; 

	const int noiseLowerLeft  = static_cast<int>(biomesMap[0][0]);
	const int noiseUpperLeft  = static_cast<int>(biomesMap[0][size]);
	const int noiseLowerRight = static_cast<int>(biomesMap[size][0]);
	const int noiseUpperRight = static_cast<int>(biomesMap[size][size]);

	return	noiseLowerLeft == noiseLowerRight && 
			noiseUpperRight == noiseLowerRight &&
			noiseUpperLeft == noiseUpperRight;
}

Biome& BiomePlacer::GetBiomeAt(const float noise) const
{
	if (noise < 0)
	{
		return _biomes.at(0);
	}
	return _biomes.at(1);
}

BiomePlacer::BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes) : _noise(std::move(noise2D)), _biomes(biomes)
{
}

void BiomePlacer::PaintChunk(const glm::ivec3 origin, ChunkData& chunk, const int size) const
{
	const auto biomesMapNoise = _noise.GetNoise(origin, size);

	if (HasChunkOnlySingleBiome(biomesMapNoise))
	{
		const auto biome = GetBiomeAt(biomesMapNoise[0][0]);
		biome.PaintChunk(origin, chunk, size);

		return;
	}

	for (auto x = 0; x < size; ++x)
	{
		for (auto y = 0; y < size; ++y)
		{
			const auto biome = GetBiomeAt(biomesMapNoise[x][y]);
			
			biome.PaintColumn(origin, chunk, size, x, 0, y);
		}
	}
}

std::vector<std::vector<std::vector<float>>> BiomePlacer::GetChunkNoiseWithBorders(const glm::ivec3 origin, const int size) const
{
	const auto sizeWithBorders = size + 2;
	const auto biomesMapNoise = _noise.GetNoise(origin, sizeWithBorders, -1, -1);

	if (HasChunkOnlySingleBiome(biomesMapNoise))
	{
		const auto biome = GetBiomeAt(biomesMapNoise[0][0]);
		return biome.GetNoise(origin, sizeWithBorders, -1, -1, -1);
	}

	std::vector<std::vector<std::vector<float>>> noise;
	ChunkUtils::InitializeVector3D(noise, sizeWithBorders);

	for (auto x = 0; x < sizeWithBorders; ++x)
	{
		for (auto z = 0; z < sizeWithBorders; ++z)
		{
			const auto biome = GetBiomeAt(biomesMapNoise[x][z]);
			const auto column = biome.GetColumnNoise(origin, sizeWithBorders, x, 0, z);

			for (auto y = 0; y < sizeWithBorders; ++y)
			{
				noise[x][y][z] = column[y];
			}
		}
	}

	return noise;
}
