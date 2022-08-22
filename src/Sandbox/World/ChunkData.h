#pragma once
#include <vector>

#include "Sandbox/Block.h"

class ChunkData
{
public:
	std::vector<std::vector<std::vector<bool>>> isBlockVisibleAt = {{}};
	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> blocks;
};
