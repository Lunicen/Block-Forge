#pragma once
#include "Sandbox/Utils/Noise.h"
#include "Sandbox/Block.h"

class Biome
{
	std::string _name;
	Noise _noise;
	Shader& _blockShader;

public:
	explicit Biome(std::string name, Noise noise, Shader& blockShader);

	void PaintColumn(std::vector<std::vector<std::vector<Block*>>>& blocks, glm::vec3 origin, int chunkSize, int offsetX, int offsetY, int offsetZ) const;
	void PaintChunk(std::vector<std::vector<std::vector<Block*>>>& blocks, glm::vec3 origin, int chunkSize) const;

	std::string GetName() const;
};

