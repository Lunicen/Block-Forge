#pragma once
#include <glad/glad.h>

#include "Biomes/BiomePlacer.h"
#include "Biomes/BiomeProvider.h"

/// @class WorldGenerator
/// @brief Handles generating the world.
///	@details This class is made for transforming chunks according to the biomes that are specified in it.
class WorldGenerator
{
	std::unique_ptr<BiomePlacer> _placer;
	std::vector<Biome> _biomes;
	int _seed;
	Texture _texture = Texture("src/Data/Textures/Dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	static void OptimizeChunkAt(int x, int y, int z, ChunkBlocks& blocks, const std::vector<std::vector<std::vector<float>>>& surroundingNoise);
	void OptimizeChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;

public:

	/// The constructor.
	///	@param seed - the world seed.
	///	@param blockShader - a reference specified for the @ref Biome class.
	explicit WorldGenerator(int seed, Shader& blockShader);

	/// @brief Adapts chunk at specified origin, according to the world terrain noise.
	///	@details This class transforms chunks by using specified biomes that are incorporated
	///	in the world generator.
	///	@param frame - the frame of the chunk.
	///	@param blocks - the blocks inside the chunk.
	void PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;
};
