#include "BlocksHandler.h"

#include "BlocksProvider.h"

BlocksHandler::BlocksHandler(const std::string& filenameWithBlocksData)
{
	auto blockProvider = BlocksProvider(filenameWithBlocksData);
	_blockTypes = blockProvider.GetBlocks();
}

std::shared_ptr<BlockModel>& BlocksHandler::Get(const std::string& blockName)
{
	return _blockTypes[blockName];
}