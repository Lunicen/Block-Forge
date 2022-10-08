#include "ChunkBuilder.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
std::unique_ptr<Chunk> ChunkBuilder::Build(ChunkFrame frame, WorldGenerator& generator) const
{
	const auto chunkFrame = ChunkFrame{frame.origin, frame.size};

	ChunkBlocks chunkBlocks;
	chunkBlocks.resize(frame.size * frame.size * frame.size);

	generator.PaintChunk(chunkFrame, chunkBlocks);

	return std::make_unique<Chunk>(frame, std::move(chunkBlocks), generator.GetBlockMap());
}
