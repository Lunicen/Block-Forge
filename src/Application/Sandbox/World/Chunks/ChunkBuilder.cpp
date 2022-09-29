#include "ChunkBuilder.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
Chunk ChunkBuilder::Build(const Position origin, const size_t& size, const WorldGenerator& generator) const
{
	const auto chunkFrame = ChunkFrame{origin, size};
	ChunkBlocks chunkBlocks;

	generator.PaintChunk(chunkFrame, chunkBlocks);

	return Chunk(chunkBlocks);
}
