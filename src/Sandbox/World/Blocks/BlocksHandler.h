#pragma once
#include "BlockRenderer.h"


class BlocksHandler
{
	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	std::vector<TriangleIndexes> _faceIndices
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;

public:
	explicit BlocksHandler(const std::string& filenameWithBlocksData);

	std::shared_ptr<BlockModel> Get(const std::string& blockName) const;
};
