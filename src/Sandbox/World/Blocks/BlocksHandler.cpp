#include "BlocksHandler.h"

#include "BlocksProvider.h"

BlocksHandler::BlocksHandler(const std::string& filenameWithBlocksData)
{
	auto blockProvider = BlocksProvider(filenameWithBlocksData);
	_blockTypes = blockProvider.GetBlocks(_faceIndices, _blockShader);
}

std::shared_ptr<BlockModel> BlocksHandler::Get(const std::string& blockName) const
{
	return _blockTypes.at(blockName);
}
