#include "BiomePlacer.h"

#include "Sandbox/Utils/World/ChunkUtils.h"

bool BiomePlacer::HasChunkOnlySingleBiome(const glm::ivec3 origin, const int size) const
{
	const auto border = size - 1;
	constexpr auto epsilon = 0.0001f;

	const auto noiseLowerLeft  = _noise.GetNoiseAt(origin, size, 0, 0);
	const auto noiseUpperLeft  = _noise.GetNoiseAt(origin, size, 0, border);
	const auto noiseLowerRight = _noise.GetNoiseAt(origin, size, border, 0);
	const auto noiseUpperRight = _noise.GetNoiseAt(origin, size, border, border);

	return	fabs(noiseLowerLeft - noiseLowerRight) < epsilon && 
			fabs(noiseUpperRight - noiseLowerRight) < epsilon &&
			fabs(noiseUpperLeft - noiseUpperRight) < epsilon;
}

Biome& BiomePlacer::GetBiomeAt(const float noise) const
{
	return _biomes.at(static_cast<int>(noise) % _biomes.size());
}

BiomePlacer::BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes) : _noise(std::move(noise2D)), _biomes(biomes)
{
}

void BiomePlacer::PaintChunk(const glm::ivec3 origin, ChunkData& chunk, const int size) const
{
	const auto chunkArea = glm::ivec2(origin.x, origin.y);

	if (HasChunkOnlySingleBiome(origin, size))
	{
		const auto biome = GetBiomeAt(_noise.GetNoiseAt(chunkArea, size, 0, 0));
		biome.PaintChunk(origin, chunk, size);

		return;
	}

	for (auto x = 0; x < size; ++x)
	{
		for (auto y = 0; y < size; ++y)
		{
			const auto biome = GetBiomeAt(_noise.GetNoiseAt(chunkArea, size, x, y));
			biome.PaintColumn(origin, chunk, size, x, 0, y);
		}
	}
}

std::vector<std::vector<std::vector<float>>> BiomePlacer::GetChunkNoiseWithBorders(const glm::ivec3 origin, const int size) const
{
	const auto chunkArea = glm::ivec2(origin.x, origin.y);

	if (HasChunkOnlySingleBiome(origin, size))
	{
		const auto biome = GetBiomeAt(_noise.GetNoiseAt(chunkArea, size, 0, 0));
		return biome.GetNoiseWithBorders(origin, size);
	}

	const auto sizeWithBorders = size + 2;
	std::vector<std::vector<std::vector<float>>> noise;
	ChunkUtils::InitializeVector3D(noise, size + 2);

	for (auto x = 0; x < sizeWithBorders; ++x)
	{
		for (auto z = 0; z < sizeWithBorders; ++z)
		{
			const auto biome = GetBiomeAt(_noise.GetNoiseAt(chunkArea, size, x - 1, z - 1));
			const auto column = biome.GetColumnNoise(origin, size, x, 0, z);

			for (auto y = 0; y < sizeWithBorders; ++y)
			{
				noise[x][y][z] = column[y];
			}
		}
	}

	return noise;
}
