#pragma once
#include "Core/Metadata.h"
#include "Application/Sandbox/Model/BlockModel.h"

/// @class BlockProvider
///	@brief Provides all the blocks mentioned in the file.
class BlockProvider
{
	Metadata _blocksMetadata;

public:

	/// @brief The constructor.
	///	@param filenameWithBlocksData - Path to the JSON file containing the blocks metadata.
	explicit BlockProvider(const std::string& filenameWithBlocksData);

	/// @brief Provides the map of the built blocks.
	///	@param blockIndices - Indices of a block (for optimization purposes).
	/// @param blockShader - Shader of a block (for optimization purposes).
	/// @param blocksSetName - Name of the blocks set that is used for this particular block map.
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> GetBlocks(std::vector<TriangleIndexes>& blockIndices, Shader& blockShader, const std::string& blocksSetName = "default");
};

