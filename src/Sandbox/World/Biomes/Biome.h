#pragma once
#include "Sandbox/Utils/World/Noise.h"
#include "Sandbox/World/ChunkData.h"

/// @class Biome
/// @brief Represents biome that could be used for terrain generation.
///	@details This class brings to life the data specified in the JSON file that specifies the biome behavior.
class Biome
{
	std::string _name;
	Noise _noise;
	Shader& _blockShader;

	void SetBlockAccordingToNoise(std::unique_ptr<Block>& block, float xBlock, float yBlock, float zBlock,
	                              float noise) const;

public:
	
	/// @brief The constructor.
	/// @param name - name of the Biome.
	/// @param noise - noise class that has specified the procedural generation algorithm of the biome. 
	/// @param blockShader - shader of the block, so the biome could be rendered.
	explicit Biome(std::string name, Noise noise, Shader& blockShader);

	/// @brief Adapts chunk to the biome algorithm.
	///	@details The purpose of this method is to "paint" the chunk
	///	according to the biome noise with respect of the origin of that chunk.
	/// @param origin - origin of the chunk.
	/// @param data - the metadata of the chunk (basically blocks).
	/// @param size - the size of the chunk (in one dimension).
	void PaintChunk(glm::ivec3 origin, ChunkData& data, int size) const;

	/// @brief Get chunk noise that is at certain position on the map.
	/// @param origin - origin of the chunk.
	/// @param size - the size of the chunk (in one dimension).
	std::vector<std::vector<std::vector<float>>> GetChunkNoise(glm::ivec3 origin, int size) const;

	/// @brief Get chunk noise that is at certain position on the map, including the noise around it.
	/// @param origin - origin of the chunk.
	/// @param size - the size of the chunk (in one dimension).
	std::vector<std::vector<std::vector<float>>> GetChunkNoiseWithBorders(glm::ivec3 origin, int size) const;
};

