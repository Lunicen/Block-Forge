#pragma once
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"
#include "Application/Layer/Sandbox/Hud.h"

/// @class PlaceBlock
///	@brief The class that place new blocks
class PlaceBlock {

public:
	/// @brief Destroy block in front of the camera
	///	@param orientation - orientation of the camera
	///	@param position - position of the camera
	/// @param chunks - the map with chunks with their positions
	///	@param blockMap - block map, which is used to place them inside chunks based on the biome noise.
	///	@param heldItem - type of block, which is used to place
	static void PlaceBlock::Place(glm::vec3 orientation, glm::vec3 position, HashMap<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap, std::string heldItem);
};