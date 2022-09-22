#pragma once
#include "BlocksProvider.h"
#include "Sandbox/Model/BlockModel.h"

class BlocksMap
{
	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	std::vector<TriangleIndexes> _faceIndices
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;

public:
	explicit BlocksMap(const std::string& filenameWithBlocksData)
	{
		auto blockProvider = BlocksProvider(filenameWithBlocksData);
		_blockTypes = blockProvider.GetBlocks(_faceIndices, _blockShader);
	}

	std::shared_ptr<BlockModel>& Get(const std::string& blockName)
	{
		return _blockTypes.at(blockName);
	}
};
