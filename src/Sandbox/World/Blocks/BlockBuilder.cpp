#include "BlockBuilder.h"

BlockBuilder::BlockBuilder(std::string textureAtlasFilename, const size_t slotSize)
	: _slotSize(slotSize), _textureAtlasFilename(std::move(textureAtlasFilename))
{
}

/*BlockModel BlockBuilder::Build(const JsonData& blockData)
{
	const auto& texture = blockData["texture"];

	//auto test = texture["front"].value();

	return BlockModel(_faceMeshes, BlockFaceTextures{});
}*/

