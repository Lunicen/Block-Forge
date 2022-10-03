#include "Biome.h"


void Biome::SetBlockAccordingToNoise(ChunkBlocks& blocks, const glm::ivec3 origin, const std::vector<float>& noise, const size_t yLevel) const
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

	const BlockVisibility blockData = 
	{
		_blocksMap.Get(_depthLevel[blockIndex].second)
	};

	blocks[origin] = blockData;
}

Biome::Biome(std::string name, const Noise3D& noise, std::vector<std::pair<size_t, std::string>> depthLevels, BlockMap& blocksMap)
	: Noise3D(noise), _name(std::move(name)), _depthLevel(std::move(depthLevels)), _blocksMap(blocksMap)
{
}

void Biome::PaintColumn(const ChunkFrame& frame, ChunkBlocks& blocks, const int xOffset, const int yOffset, const int zOffset) const
{
	const auto& x = xOffset;
	const auto& z = zOffset;

	const auto noise = GetColumnNoiseWithAdditionalHeight(
		frame,
		xOffset, yOffset, zOffset, 
		_depthLevel.back().first
	);

	const auto origin = frame.origin * static_cast<int>(frame.size);

	for (size_t y = 0; y < frame.size; ++y)
	{
		SetBlockAccordingToNoise(
			blocks,
			origin + glm::ivec3(x, y, z),
			noise, y
		);
	}
}
