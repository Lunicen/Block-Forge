#include "BlocksProvider.h"

BlocksProvider::BlocksProvider(const std::string& filenameWithBlocksData)
{
	_blocksMetadata.Load(filenameWithBlocksData);
}

std::map<std::string, std::unique_ptr<BlockModel>> BlocksProvider::GetBlocks(
	const std::vector<std::string>& blocksTextureNames,
	const std::string& blocksSetName)
{
	auto blocksAtlas = std::map<std::string, BlockModel>();
	auto blocksSet = _blocksMetadata.GetJsonObject(blocksSetName);

	for (const auto& blockName : blocksTextureNames)
	{
		auto front = BlockFaceModel()

		blocksAtlas[blockName] = 
	}
	const auto id = pattern["id"].get<std::string>();
	const auto frequency = pattern["frequency"].get<float>();

	return {id, seed, frequency};
}
