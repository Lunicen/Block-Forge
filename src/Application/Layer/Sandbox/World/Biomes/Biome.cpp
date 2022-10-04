#include "Biome.h"

void Biome::SetBlockAccordingToNoise(ChunkBlocks& blocks, const glm::ivec3 origin, const std::vector<float>& noise, const size_t yLevel, const Byte& visibilityFlags) const
{
	if (noise[yLevel] > 0) return;

	auto blockIndex = _depthLevel.size() - 1;
	while (blockIndex > 0)
	{
		const auto& noiseOverThisBlock = yLevel + _depthLevel[blockIndex].first;
		if (noise[noiseOverThisBlock] <= 0)
		{
			break;
		}

		--blockIndex;
	}

	const BlockData blockData = 
	{
		_blocksMap.GetId(_depthLevel[blockIndex].second),
		visibilityFlags
	};

	blocks[origin] = blockData;
}

Biome::Biome(std::string name, const Noise3D& noise, std::vector<std::pair<size_t, std::string>> depthLevels, BlockMap& blocksMap)
	: Noise3D(noise), _name(std::move(name)), _depthLevel(std::move(depthLevels)), _blocksMap(blocksMap)
{
}

void Biome::PaintBlockAt(const Position& origin, const ChunkFrame& frame, ChunkBlocks& blocks, const Byte& visibilityFlags) const
{
	const auto noise = GetColumnNoiseWithAdditionalHeight(
		frame,
		origin.x, origin.y, origin.z, 
		_depthLevel.back().first
	);

	SetBlockAccordingToNoise(
		blocks,
		frame.origin * static_cast<int>(frame.size) + origin,
		noise, origin.y,
		visibilityFlags
	);
}
