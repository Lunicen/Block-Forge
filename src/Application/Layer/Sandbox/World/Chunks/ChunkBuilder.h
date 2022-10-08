#pragma once
#include "Application/Layer/Sandbox/World/WorldGenerator.h"
#include "Structure/Chunk.h"

/// @class ChunkBuilder
///	@brief Builds chunks.
class ChunkBuilder
{
public:

	/// @brief Builds the chunk.
	///	@param frame - Frame of the chunk.
	///	@param generator - The world generator that chunk uses to generate it's content.
	std::unique_ptr<Chunk> Build(ChunkFrame frame, WorldGenerator& generator) const;
};

