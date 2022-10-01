#include "ChunkBuilder.h"

#include "Application/Sandbox/World/Biomes/Biome.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
std::unique_ptr<Chunk> ChunkBuilder::Build(const Position origin, const size_t& size, WorldGenerator& generator) const
{
	const auto chunkFrame = ChunkFrame{origin, size};
	ChunkBlocks chunkBlocks;

	generator.PaintChunk(chunkFrame, chunkBlocks);

	return std::make_unique<Chunk>(chunkBlocks, generator.GetBlockMap().GetBlocksTexture(), size, generator.GetBlockMap().GetBlocksShader());
}
