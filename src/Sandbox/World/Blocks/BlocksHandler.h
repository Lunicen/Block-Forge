#pragma once
#include "BlockRenderer.h"


class BlocksHandler
{
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;

public:
	explicit BlocksHandler(const std::string& filenameWithBlocksData);

	std::shared_ptr<BlockModel>& Get(const std::string& blockName);
};
