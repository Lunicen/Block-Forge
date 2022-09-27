#pragma once
#include "Application/Sandbox/World/WorldGenerator.h"
#include "Structure/Chunk.h"

class ChunkBuilder
{
public:
	Chunk Build(Position origin, const size_t& size, const WorldGenerator& generator) const;
};

