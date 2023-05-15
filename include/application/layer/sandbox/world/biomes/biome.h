#pragma once
#include "application/layer/sandbox/noise/noise3d.h"
#include "application/layer/sandbox/world/blocks/block_map.h"
#include "application/layer/sandbox/world/chunks/structure/chunk_blocks.h"

/// @class Biome
/// @brief Represents biome that could be used for terrain generation.
///	@details This class brings to life the data specified in the JSON file that specifies the biome behavior.
class Biome final : public Noise3D
{
	std::string _name;
	std::vector<std::pair<size_t, std::string>> _depthLevel;
	BlockMap& _blocksMap;

	void SetBlockAccordingToNoise(const glm::ivec3& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const std::vector<float>& noise, const Byte& visibilityFlags) const;

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
	/// @param origin - position of the block to paint (relative to the chunk, not world direct coordinates).
	/// @param frame - frame of the chunk.
	/// @param blocks - the metadata of the chunk (basically blockAt).
	/// @param visibilityFlags - calculated visibility flags of the block.
	void PaintBlockAt(const Position& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const Byte& visibilityFlags) const;
};

