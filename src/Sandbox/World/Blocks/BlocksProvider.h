#pragma once
#include "BlockBuilder.h"
#include "Core/Metadata.h"
#include "Sandbox/Model/BlockModel.h"


class BlocksProvider
{
	Metadata _blocksMetadata;
	std::unique_ptr<BlockBuilder> _blockBuilder;

public:
	explicit BlocksProvider(const std::string& filenameWithBlocksData);

	std::map<std::string, std::unique_ptr<BlockModel>> GetBlocks(const std::vector<std::string>& blocksTextureNames, const std::string& blocksSetName = "default");
};

