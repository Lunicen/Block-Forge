#pragma once
#include "Sandbox/Utils/Noise.h"
#include "Sandbox/World/Chunk.h"

class Biome
{
	std::string _name;
	Noise _noise;
	Shader& _blockShader;

public:
	explicit Biome(std::string name, Noise noise, Shader& block);

	void PaintColumn();
	void PaintChunk(Chunk& chunk, int chunkSize);

	void GetName();
};

