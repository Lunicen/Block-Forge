#pragma once
#include "BlockProvider.h"
#include "Application/Sandbox/Model/BlockModel.h"

/// @class BlockMap
///	@brief Represents a map of the blocks that could be used to place in the chunks.
class BlockMap
{
	Shader _blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	std::vector<TriangleIndexes> _faceIndices
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;

public:

	/// @brief Copy constructor.
	BlockMap(const BlockMap&) = default;

	/// @brief Move constructor.
	BlockMap(BlockMap&&) noexcept = default;

	/// @brief Copy assignment constructor.
	BlockMap &operator=(const BlockMap&) = delete;

	/// @brief Move assignment constructor.
	BlockMap &operator=(const BlockMap&&) noexcept = delete;

	/// @brief The constructor.
	///	@param filenameWithBlocksData - Path to the JSON file containing the blocks metadata.
	explicit BlockMap(const std::string& filenameWithBlocksData)
	{
		auto blockProvider = BlockProvider(filenameWithBlocksData);
		_blockTypes = blockProvider.GetBlocks(_faceIndices, _blockShader);
	}

	/// @brief Returns the block model based on it's name.
	/// @param blockName - name of the block.
	std::shared_ptr<BlockModel>& Get(const std::string& blockName)
	{
		return _blockTypes.at(blockName);
	}

	~BlockMap() = default;
};
