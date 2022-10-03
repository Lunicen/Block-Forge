#pragma once
#include "BlockProvider.h"
#include "Application/Layer/Sandbox/Model/BlockModel.h"
#include "Application/Layer/Sandbox/Model/Surface/TextureAtlas.h"

/// @class BlockMap
///	@brief Represents a map of the blocks that could be used to place in the chunks.
class BlockMap
{
	std::shared_ptr<TextureAtlas> _blockTextures{};
	std::unordered_map<std::string, std::shared_ptr<BlockModel>> _blockTypes;
	Shader _blockShader{"src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag"};

public:

	/// @brief Copy constructor.
	BlockMap(const BlockMap&) = delete;

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

		const auto& textureName = blockProvider.GetTextureAtlasFilename();
		const auto& textureSlotSize = blockProvider.GetTextureAtlasSlotSize();

		_blockTextures = std::make_shared<TextureAtlas>(textureName, textureSlotSize);
		_blockTypes = blockProvider.GetBlocks(*_blockTextures);
	}

	/// @brief Returns the block model based on it's name.
	/// @param blockName - name of the block.
	std::shared_ptr<BlockModel>& Get(const std::string& blockName)
	{
		return _blockTypes.at(blockName);
	}

	/// @brief An operator that allows to get the block by its key in a convenient way.
	std::shared_ptr<BlockModel>& operator[](const std::string& blockName)
	{
		return _blockTypes.at(blockName);
	}

	/// @brief Returns the texture atlas that is used in this map.
	std::shared_ptr<TextureAtlas>& GetBlocksTexture()
	{
		return _blockTextures;
	}

	/// @brief Returns the blocks shader. 
	Shader& GetBlocksShader()
	{
		return _blockShader;
	}

	~BlockMap() = default;
};
