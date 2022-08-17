#pragma once
#include "Sandbox/Utils/Noise.h"
#include "Sandbox/World/Chunk.h"

class Biome
{
	std::string _name;
	Noise _noise;

public:
	explicit Biome(std::string name, Noise noise);

	void PaintColumn();
	void PaintChunk(Chunk& chunk);

	void GetName();
};

