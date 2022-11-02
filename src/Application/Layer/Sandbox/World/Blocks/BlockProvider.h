#pragma once
#include "Core/Metadata.h"
#include "Application/Layer/Sandbox/Model/BlockModel.h"
#include "Application/Layer/Sandbox/Model/Surface/TextureAtlas.h"

constexpr size_t MaxBlocksAmount = 256;

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
	HashMap<std::string, std::shared_ptr<BlockModel>> GetBlocks(TextureAtlas& blocksTextureAtlas, const std::string& blocksSetName = "default");

	/// @brief Sets the blocks ID array and their "names" array, based on the given set.
	///	@param blockArray - reference to the block IDs array.
	///	@param blockNames - reference to the block names array.
	///	@param blocksTextureAtlas - the texture atlas that is shared among the blocks.
	///	@param blocksSetName - name of the set to provide the blocks from.
	void SetBlocks(std::array<std::shared_ptr<BlockModel>, MaxBlocksAmount>& blockArray,
	               HashMap<std::string, unsigned char>& blockNames, 
	               TextureAtlas& blocksTextureAtlas,
	               const std::string& blocksSetName = "default");

	/// @brief Returns texture atlas filename of the blocks set.
	///	@param blocksSetName - Name of the blocks set.
	std::string GetTextureAtlasFilename(const std::string& blocksSetName = "default");

	/// @brief Returns the sprite size defined in the set data.
	///	@param blocksSetName - Name of the blocks set.
	size_t GetTextureAtlasSlotSize(const std::string& blocksSetName = "default");
};

