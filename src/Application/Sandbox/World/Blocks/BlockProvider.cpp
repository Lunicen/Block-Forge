#include "BlockProvider.h"

#include "BlockBuilder.h"

BlockProvider::BlockProvider(const std::string& filenameWithBlocksData)
{
	_blocksMetadata.Load(filenameWithBlocksData);
}

std::unordered_map<std::string, std::shared_ptr<BlockModel>> BlockProvider::GetBlocks(
	const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);

	const std::string textureAtlasName = blocksSet.value("atlas", "");
	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
	const size_t slotSize = blocksSet.value("slotSize", 0);

	const auto builder = BlockBuilder(textureAtlasName, slotSize);
	auto blocks = std::unordered_map<std::string, std::shared_ptr<BlockModel>>();

	for (const auto& blockData : blocksSet["blocks"])
	{
		const std::string name = blockData.value("block", "unknown");
		blocks[name] = std::make_shared<BlockModel>(builder.Build(blockData));
	}

	return blocks;
}

TextureAtlas&& BlockProvider::GetBlocksTextures(const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);

	const std::string textureAtlasName = blocksSet.value("atlas", "");
	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
	const size_t slotSize = blocksSet.value("slotSize", 0);

	return std::move(TextureAtlas(textureAtlasName, slotSize));
}
