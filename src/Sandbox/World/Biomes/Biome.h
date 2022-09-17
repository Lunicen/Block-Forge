#pragma once
#include "Sandbox/Noise/Noise3D.h"
#include "Sandbox/World/Blocks/BlocksQueue.h"
#include "Sandbox/World/Chunks/Structure/ChunkBlocks.h"

/// @class Biome
/// @brief Represents biome that could be used for terrain generation.
///	@details This class brings to life the data specified in the JSON file that specifies the biome behavior.
class Biome final : public Noise3D
{
	std::string _name;
	BlocksQueue& _blocksQueue;

	void SetBlockAccordingToNoise(std::shared_ptr<BlockModel>& block, glm::ivec3 origin, float noise) const;

public:
	
	/// @brief The constructor.
	/// @param name - name of the Biome.
	/// @param noise - noise class that has specified the procedural generation algorithm of the biome. 
	explicit Biome(std::string name, const Noise3D& noise, std::reference_wrapper<BlocksQueue> blocksQueue);

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

