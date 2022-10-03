#pragma once
#include "Core/Metadata.h"
#include "Application/Layer/Sandbox/Model/BlockModel.h"
#include "Application/Layer/Sandbox/Model/Surface/TextureAtlas.h"

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
	/// @param blocksTextureAtlas - Texture atlas of the blocks to be built.
	/// @param blocksSetName - Name of the blocks set that is used for this particular block map.
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> GetBlocks(TextureAtlas& blocksTextureAtlas, const std::string& blocksSetName = "default");

	/// @brief Returns texture atlas filename of the blocks set.
	///	@param blocksSetName - Name of the blocks set.
	std::string GetTextureAtlasFilename(const std::string& blocksSetName = "default");

	/// @brief Returns the sprite size defined in the set data.
	///	@param blocksSetName - Name of the blocks set.
	size_t GetTextureAtlasSlotSize(const std::string& blocksSetName = "default");
};

