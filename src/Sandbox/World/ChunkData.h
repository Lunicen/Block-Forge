#pragma once
#include <vector>

#include "Sandbox/Block.h"

class ChunkData
{
protected:
	std::vector<std::vector<std::vector<bool>>> _isVisible = {{}};
	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> _blocks = {{}};

	void TransferChunkDataToThis(ChunkData& from);

public:
	std::vector<std::vector<std::vector<bool>>> GetVisibilityVector() const;
	void SetVisibilityVector(const std::vector<std::vector<std::vector<bool>>>& isVisible);

	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> GetBlocks() const;
	void SetBlocks(const std::vector<std::vector<std::vector<std::unique_ptr<Block>>>>& blocks);
};

inline void ChunkData::TransferChunkDataToThis(ChunkData& from)
{
	_isVisible = std::move(from._isVisible);
	_blocks = std::move(from._blocks);
}

inline std::vector<std::vector<std::vector<bool>>> ChunkData::GetVisibilityVector() const
{
	return _isVisible;
}

inline void ChunkData::SetVisibilityVector(const std::vector<std::vector<std::vector<bool>>>& isVisible)
{
	_isVisible = isVisible;
}

inline std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> ChunkData::GetBlocks() const
{
	return _blocks;
}

inline void ChunkData::SetBlocks(const std::vector<std::vector<std::vector<std::unique_ptr<Block>>>>& blocks)
{
	_blocks = blocks;
}

