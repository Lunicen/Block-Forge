#pragma once
#include "Biomes/BiomeProvider.h"

/// @class WorldGenerator
/// @brief Handles generating the world.
///	@details This class is made for transforming chunks according to the biomes that are specified in it.
class WorldGenerator
{
	std::vector<Biome> _biomes;
	int _seed;

	static void OptimizeChunkAt(int x, int y, int z, ChunkData& data, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);
	static void OptimizeChunk(ChunkData& data, const std::vector<std::vector<std::vector<float>>>& noiseOfChunkWithBorders);

public:

	/// The constructor.
	///	@param seed - the world seed.
	explicit WorldGenerator(int seed);

	/// @brief Initialize the world generator and load the data from the JSON file.
	///	@param blockShader - a reference specified for the @ref Biome class.
	void Initialize(Shader& blockShader);

	/// @brief Adapts chunk at the specified origin, according to the world terrain noise.
	///	@details This class transforms chunks by using specified biomes that are incorporated
	///	in the world generator.
	///	@param chunk - the chunk data for blocks manipulation.
	///	@param origin - the origin of the chunk.
	///	@param size - the size of the chunk.
	void PaintChunk(ChunkData& chunk, glm::ivec3 origin, int size) const;

	/// @brief If the method @ref Initialize(Shader& blockShader) was used, returns true. Otherwise false.
	bool IsInitialized() const;
};
