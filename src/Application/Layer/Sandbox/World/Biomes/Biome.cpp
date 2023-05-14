#include "application/layer/sandbox/world/biomes/biome.h"
#include "application/layer/sandbox/world/chunks/chunk_utils.h"

void Biome::SetBlockAccordingToNoise(const glm::ivec3& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const std::vector<float>& noise, const Byte& visibilityFlags) const
{
	auto blockIndex = _depthLevel.size() - 1;
	while (blockIndex > 0)
	{
		const auto& yLevelOverThisBlock = _depthLevel[blockIndex].first;
		if (noise[yLevelOverThisBlock] < 0.0f)
		{
			break;
		}

		--blockIndex;
	}

	Byte blockFlags = visibilityFlags;
	blockFlags |= BlockFlag.activate; // Enables block, so it's not treated as an air.

	const BlockData blockData = 
	{
		_blocksMap.GetId(_depthLevel[blockIndex].second),
		blockFlags
	};

	blocks[ChunkUtils::GetBlockIndex(origin, frame.size)] = BlockData(blockData);
}

Biome::Biome(std::string name, const Noise3D& noise, std::vector<std::pair<size_t, std::string>> depthLevels, BlockMap& blocksMap)
	: Noise3D(noise), _name(std::move(name)), _depthLevel(std::move(depthLevels)), _blocksMap(blocksMap)
{
}

void Biome::PaintBlockAt(const Position& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const Byte& visibilityFlags) const
{
	const auto noise = GetNoiseAtWithTopColumn(
		origin + frame.origin * static_cast<int>(frame.size),
		_depthLevel.back().first
	);

	SetBlockAccordingToNoise(
		origin,
		frame,
		blocks,
		noise,
		visibilityFlags
	);
}
