#pragma once
#include "Biome.h"
#include "Core/Metadata.h"
#include "Application/Sandbox/Noise/Noise2D.h"

/// @class BiomeProvider
/// @brief Provides the biomes specified in the JSON file.
///	@details This class manages creating the list of biomes that are specified in the JSON file.
///	It's purpose is to provide all the defined biomes from the file in a convenient way.
class BiomeProvider
{
	BlockMap& _blockMap;
	Metadata _biomesMetadata;

public:

	/// @brief The constructor.
	///	@param filenameWithBiomeData - File containing the metadata related to biomes.
	/// @param blockMap - block map, which is used to place them inside chunks based on the biome noise.
	explicit BiomeProvider(const std::string& filenameWithBiomeData, BlockMap& blockMap);

	/// @brief Get noise that is used by placer that represents world map.
	///	@param seed - a seed of the world map noise.
	///	@param biomesType - type of biomes that we want to apply, to the world.
	Noise2D GetPlacerNoise(int seed, const std::string& biomesType = "default");

	/// @brief Get all the biomes specified in the file with a particular type.
	///	@param seed - a seed of the biome noises.
	///	@param biomesType - type of biomes that we want to apply, to the world.
	std::vector<Biome> GetBiomes(int seed, const std::string& biomesType = "default");
};

