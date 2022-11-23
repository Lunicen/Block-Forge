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
	//oscyluje od -1 do 1
	if (noise > 0 && noise < 0.5)
	{
		return _biomes.at(0);
	}
	else if (noise >= 0.5)
	{
		return _biomes.at(1);
	}
	else if (noise < 0 && noise >= 0.5)
	{
		return _biomes.at(2);
	}
	else
	{
		return _biomes.at(3);
	}
}

Byte BiomePlacer::GetBlockVisibilityFlags(const Position& origin, const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders)
{
	const auto& x = origin.x + 1;
	const auto& y = origin.y + 1;
	const auto& z = origin.z + 1;

	Byte visibilityFlags = 0;

	visibilityFlags |= chunkNoiseWithBorders[x - 1][y][z] > 0 ? BlockFlag.leftFace   : 0;
	visibilityFlags |= chunkNoiseWithBorders[x + 1][y][z] > 0 ? BlockFlag.rightFace  : 0;
	visibilityFlags |= chunkNoiseWithBorders[x][y - 1][z] > 0 ? BlockFlag.bottomFace : 0;
	visibilityFlags |= chunkNoiseWithBorders[x][y + 1][z] > 0 ? BlockFlag.topFace    : 0;
	visibilityFlags |= chunkNoiseWithBorders[x][y][z - 1] > 0 ? BlockFlag.frontFace  : 0;
	visibilityFlags |= chunkNoiseWithBorders[x][y][z + 1] > 0 ? BlockFlag.backFace   : 0;

	return visibilityFlags;
}

bool BiomePlacer::IsAir(const Position& origin,
	const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders)
{
	return chunkNoiseWithBorders[origin.x + 1][origin.y + 1][origin.z + 1] > 0 ? true : false;
}

void BiomePlacer::PaintBlockAt(const Position& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const std::vector<std::vector<std::vector<float>>>& chunkNoiseWithBorders, const std::vector<std::vector<float>>& biomesMapNoise) const
{
	if (IsAir(origin, chunkNoiseWithBorders))
	{
		return;
	}

	const Byte visibilityFlags = GetBlockVisibilityFlags(origin, chunkNoiseWithBorders);

	const auto biome = GetBiomeAt(biomesMapNoise[origin.x][origin.z]);
	biome.PaintBlockAt(
		origin,
		frame,
		blocks,
		visibilityFlags
	);
}

BiomePlacer::BiomePlacer(Noise2D noise2D, std::vector<Biome>& biomes) : _noise(std::move(noise2D)), _biomes(biomes)
{
}

void BiomePlacer::PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const
{
	const auto biomesMapNoise = _noise.GetNoise(frame);
	const auto chunkNoiseWithBorders = GetChunkNoise(frame, 1);

	for (size_t x = 0; x < frame.size; ++x)
	{
		for (size_t y = 0; y < frame.size; ++y)
		{
			for (size_t z = 0; z < frame.size; ++z)
			{
				PaintBlockAt(Position(x, y, z), frame, blocks, chunkNoiseWithBorders, biomesMapNoise);
			}
		}
	}
}

std::vector<std::vector<std::vector<float>>> BiomePlacer::GetChunkNoise(const ChunkFrame& frame, const int expansionFactor) const
{
	const auto sizeWithBorders = frame.size + static_cast<size_t>(2) * expansionFactor;
	const auto biomesMapNoise = _noise.GetNoise(frame, expansionFactor);

	if (HasChunkOnlySingleBiome(biomesMapNoise))
	{
		const auto biome = GetBiomeAt(biomesMapNoise[1][1]);
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
