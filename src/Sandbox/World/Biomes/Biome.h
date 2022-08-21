#pragma once
#include "Sandbox/Utils/Noise.h"
#include "Sandbox/World/ChunkData.h"

class Biome
{
	std::string _name;
	Noise _noise;
	Shader& _blockShader;

	void SetBlockAccordingToNoise(std::unique_ptr<Block>& block, float x, float y, float z, float noise) const;

public:
	explicit Biome(std::string name, Noise noise, Shader& blockShader);

	void PaintColumn(glm::ivec3 origin, ChunkData& data, int chunkSize, int offsetX, int offsetY, int offsetZ) const;
	void PaintChunk(glm::ivec3 origin, ChunkData& data, int size) const;

	std::string GetName() const;
	std::vector<float> GetColumnNoise(glm::ivec3 origin, int chunkSize, int offsetX, int offsetY, int offsetZ) const;
	std::vector<float> GetChunkNoise(glm::ivec3 origin, int chunkSize) const;
};

