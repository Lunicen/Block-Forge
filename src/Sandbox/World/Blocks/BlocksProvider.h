#pragma once
#include "Core/Metadata.h"
#include "Sandbox/Model/BlockModel.h"

class BlocksProvider
{
	Metadata _blocksMetadata;

public:
	explicit BlocksProvider(const std::string& filenameWithBlocksData);

	std::unordered_map<std::string, std::shared_ptr<BlockModel>> GetBlocks(std::vector<TriangleIndexes>& blockIndices, Shader& blockShader, const std::string& blocksSetName = "default");
};

