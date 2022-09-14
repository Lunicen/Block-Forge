#include "BlockBuilder.h"

BlockBuilder::BlockBuilder(std::string textureAtlasFilename, const size_t slotSize)
	: _slotSize(slotSize), _textureAtlasFilename(std::move(textureAtlasFilename))
{
}

BlockModel BlockBuilder::Build(const JsonData& blockData)
{
	BlockFaceTextures textures{};

	for (const auto& textureData : blockData["textures"])
	{
		const auto x = textureData["location"].at(0).get<int>();
		const auto y = textureData["location"].at(1).get<int>();


		//const auto texture = std::make_shared<Texture>()
	}

	return BlockModel(_faceMeshes, textures);
}

