#include "BiomePlacer.h"

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

void BiomePlacer::PaintChunkWithBiome(const glm::ivec3 origin, ChunkData& chunk, const int size, const Biome& biome)
{
	biome.PaintChunk(origin, chunk, size);
}

BiomePlacer::BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes) : _noise(std::move(noise2D)), _biomes(biomes)
{
}

void BiomePlacer::PaintChunk(const glm::ivec3 origin, ChunkData& chunk, const int size)
{
	const auto chunkArea = glm::ivec2(origin.x, origin.y);

	if (HasChunkOnlySingleBiome(origin, size))
	{
		const auto singleBiomeIndex = static_cast<int>(_noise.GetNoiseAt(chunkArea, size, 0, 0)) % _biomes.size();
		PaintChunkWithBiome(origin, chunk, size, _biomes.at(singleBiomeIndex));
		return;
	}

	for (auto x = 0; x < size; ++x)
	{
		for (auto y = 0; y < size; ++y)
		{
			const auto selectedBiomeIndex = static_cast<int>(_noise.GetNoiseAt(chunkArea, size, x, y)) % _biomes.size();
			const auto columnNoise = _biomes.at(selectedBiomeIndex).GetColumnNoise(origin, size, x, 0, y);
		}
	}
}
