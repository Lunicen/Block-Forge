#pragma once
#include <vector>

#include "Sandbox/World/Chunk.h"

class Biome
{
protected:
	std::string _name = "Undefined chunk";

public:
	explicit Biome();

	void FillChunk(Chunk& chunk);
	void GetName();
};

