#pragma once
#include "Sandbox/Utils/ProceduralGen/Noise3D.h"
#include "Sandbox/Utils/Chunk/ChunkBlocks.h"

/// @class Biome
/// @brief Represents biome that could be used for terrain generation.
///	@details This class brings to life the data specified in the JSON file that specifies the biome behavior.
class Biome final : public Noise3D
{
	std::string _name;
	Shader& _blockShader;
	Texture& _texture;

	void SetBlockAccordingToNoise(std::unique_ptr<Block>& block, float xBlock, float yBlock, float zBlock,
	                              float noise) const;

public:
	
	/// @brief The constructor.
	/// @param name - name of the Biome.
	/// @param noise - noise class that has specified the procedural generation algorithm of the biome. 
	/// @param blockShader - shader of the block, so the biome could be rendered.
	explicit Biome(std::string name, const Noise3D& noise, Shader& blockShader, Texture& texture);

	/// @brief Adapts chunk column according to the biome noise.
	///	@details The purpose of this method is to "paint" the chunk
	///	according to the biome noise with respect of the origin of that chunk.
	/// @param frame - frame of the chunk.
	/// @param blocks - the metadata of the chunk (basically blockAt).
	/// @param xOffset - X offset from the chunk origin.
	/// @param yOffset - Y offset from the chunk origin.
	/// @param zOffset - Z offset from the chunk origin.
	void PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, int xOffset, int yOffset, int zOffset) const;

	/// @brief Adapts chunk to the biome noise.
	///	@details The purpose of this method is to "paint" the chunk
	///	according to the biome noise with respect of the origin of that chunk.
	/// @param frame - frame of the chunk.
	/// @param blocks - the metadata of the chunk (basically blockAt).
	void PaintChunk(const ChunkFrame& frame, ChunkBlocks& blocks) const;
};

