#pragma once
#include "Application/Layer/Sandbox/World/WorldGenerator.h"
#include "Structure/Chunk.h"

/// @class ChunkBuilder
///	@brief Builds chunks.
class ChunkBuilder
{
public:

	/// @brief Builds the chunk.
	///	@param origin - origin of the chunk.
	///	@param size - size of the chunks edge.
	///	@param generator - the world generator that chunk uses to generate it's content.
	std::unique_ptr<Chunk> Build(Position origin, const size_t& size, WorldGenerator& generator) const;
};

