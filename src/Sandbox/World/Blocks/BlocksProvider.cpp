#include "BlocksProvider.h"

BlocksProvider::BlocksProvider(const std::string& filenameWithBlocksData)
{
	_blocksMetadata.Load(filenameWithBlocksData);
}

std::map<std::string, std::unique_ptr<BlockModel>> BlocksProvider::GetBlocks(
	const std::vector<std::string>& blocksTextureNames,
	const std::string& blocksSetName)
{
	const auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);

	const std::string textureAtlasName = blocksSet.value("atlas", "");
	const size_t slotSize = blocksSet.value("slotSize", 0);

	_blockBuilder = std::make_unique<BlockBuilder>(textureAtlasName, slotSize);

	auto blocks = std::map<std::string, BlockModel>();
	

	/*for (const auto& blockName : blocksTextureNames)
	{
		auto front = BlockFaceModel(_blockFace.front, )

		blocksAtlas[blockName] = 
	}
	const auto id = pattern["id"].get<std::string>();
	const auto frequency = pattern["frequency"].get<float>();*/

	return {};
}
