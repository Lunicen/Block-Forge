#include "BlockProvider.h"

#include "BlockBuilder.h"

BlockProvider::BlockProvider(const std::string& filenameWithBlocksData)
{
	_blocksMetadata.Load(filenameWithBlocksData);
}

HashMap<std::string, std::shared_ptr<BlockModel>> BlockProvider::GetBlocks(
	TextureAtlas& blocksTextureAtlas,
	const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);
	auto blocks = HashMap<std::string, std::shared_ptr<BlockModel>>();

	for (const auto& blockData : blocksSet["blocks"])
	{
		const std::string name = blockData.value("block", "unknown");
		const BlockBuilder builder;

		blocks[name] = std::make_shared<BlockModel>(builder.Build(blockData, blocksTextureAtlas));
	}

	return blocks;
}

void BlockProvider::SetBlocks(
	std::array<std::shared_ptr<BlockModel>, MaxBlocksAmount>& blockArray,
	HashMap<std::string, unsigned char>& blockNames, 
	TextureAtlas& blocksTextureAtlas,
	const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);

	Byte arrayIterator = 0;
	for (const auto& blockData : blocksSet["blocks"])
	{
		const std::string name = blockData.value("block", "unknown");
		blockNames[name] = arrayIterator;

		const BlockBuilder builder;
		blockArray[arrayIterator] = std::make_shared<BlockModel>(builder.Build(blockData, blocksTextureAtlas));

		++arrayIterator;
	}
}

std::string BlockProvider::GetTextureAtlasFilename(const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);
	return blocksSet.value("atlas", "");
}

size_t BlockProvider::GetTextureAtlasSlotSize(const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);
	return blocksSet.value("slotSize", 0);
}
