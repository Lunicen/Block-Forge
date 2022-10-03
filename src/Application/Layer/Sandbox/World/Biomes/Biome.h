#pragma once
#include "Application/Layer/Sandbox/Noise/Noise3D.h"
#include "Application/Layer/Sandbox/World/Blocks/BlockMap.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/ChunkBlocks.h"

/// @class Biome
/// @brief Represents biome that could be used for terrain generation.
///	@details This class brings to life the data specified in the JSON file that specifies the biome behavior.
class Biome final : public Noise3D
{
	std::string _name;
	std::vector<std::pair<size_t, std::string>> _depthLevel;
	BlockMap& _blocksMap;

	void SetBlockAccordingToNoise(ChunkBlocks& blocks, glm::ivec3 origin, const std::vector<float>& noise, size_t yLevel) const;

public:
	
	/// @brief The constructor.
	/// @param name - name of the Biome.
	/// @param noise - noise class that has specified the procedural generation algorithm of the biome. 
	/// @param depthLevels - the starting Y levels that indicate when to start painting the chunk by using a certain block type. 
	/// @param blocksMap - block map, which is used to place them inside chunks based on the biome noise. 
	explicit Biome(std::string name, const Noise3D& noise, std::vector<std::pair<size_t, std::string>>
	               depthLevels, BlockMap& blocksMap);
	
	/// @brief Adapts chunk column according to the biome noise.
	///	@details The purpose of this method is to "paint" the chunk
	///	according to the biome noise with respect of the origin of that chunk.
	/// @param frame - frame of the chunk.
	/// @param blocks - the metadata of the chunk (basically blockAt).
	/// @param xOffset - X offset from the chunk origin.
	/// @param yOffset - Y offset from the chunk origin.
	/// @param zOffset - Z offset from the chunk origin.
	void PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, int xOffset, int yOffset, int zOffset) const;
};

