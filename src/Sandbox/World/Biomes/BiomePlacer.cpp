#include "BiomePlacer.h"


bool BiomePlacer::HasChunkOnlySingleBiome(const std::vector<std::vector<float>>& biomesMap)
{
	const auto& size = biomesMap.size() - 1; 

	const auto noiseLowerLeft  = biomesMap[0][0];
	const auto noiseUpperLeft  = biomesMap[0][size];
	const auto noiseLowerRight = biomesMap[size][0];
	const auto noiseUpperRight = biomesMap[size][size];

	constexpr float epsilon = FLT_MIN;
	return	fabs(noiseLowerLeft - noiseLowerRight) < epsilon && 
			fabs(noiseUpperRight - noiseLowerRight) < epsilon &&
			fabs(noiseUpperLeft - noiseUpperRight) < epsilon;
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

void BiomePlacer::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto biomesMapNoise = _noise.GetNoise(frame);

	/*if (HasChunkOnlySingleBiome(biomesMapNoise))
	{
		const auto biome = GetBiomeAt(biomesMapNoise[0][0]);
		biome.PaintChunk(frame, blocks);

		return;
	}*/

	for (size_t x = 0; x < frame.size; ++x)
	{
		for (size_t y = 0; y < frame.size; ++y)
		{
			const auto biome = GetBiomeAt(biomesMapNoise[x][y]);
			
			biome.PaintColumn(frame, blocks, 
				static_cast<int>(x), 
				0, 
				static_cast<int>(y)
			);
		}
	}
}

std::vector<std::vector<std::vector<float>>> BiomePlacer::GetChunkNoise(const ChunkFrame& frame, const int expansionFactor) const
{
	const auto sizeWithBorders = frame.size + static_cast<size_t>(2) * expansionFactor;
	const auto biomesMapNoise = _noise.GetNoise(frame, expansionFactor);

	if (HasChunkOnlySingleBiome(biomesMapNoise))
	{
		const auto biome = GetBiomeAt(biomesMapNoise[0][0]);
		return biome.GetNoise(frame, expansionFactor);
	}

	std::vector<std::vector<std::vector<float>>> noise;

	noise.resize(sizeWithBorders);
	for (size_t x = 0; x < sizeWithBorders; ++x)
	{
		noise[x].resize(sizeWithBorders);
		for (size_t y = 0; y < sizeWithBorders; ++y)
		{
			noise[x][y].resize(sizeWithBorders);
		}
	}

	for (size_t x = 0; x < sizeWithBorders; ++x)
	{
		for (size_t z = 0; z < sizeWithBorders; ++z)
		{
			const auto biome = GetBiomeAt(biomesMapNoise[x][z]);
			const auto column = biome.GetColumnNoise(frame, static_cast<int>(x), 0, static_cast<int>(z), 1);

			for (size_t y = 0; y < sizeWithBorders; ++y)
			{
				noise[x][y][z] = column[y];
			}
		}
	}

	return noise;
}
