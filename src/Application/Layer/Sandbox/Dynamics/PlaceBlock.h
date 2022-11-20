#pragma once
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"

/// @class PlaceBlock
///	@brief The class that place new blocks
class PlaceBlock {

public:
		/// @brief Destroy block in front of the camera
		///	@param _orientation - orientation of the camera
		///	@param _position - position of the camera
		/// @param chunks - the map with chunks with their positions
		///	@param blockMap - block map, which is used to place them inside chunks based on the biome noise.
	static void Place(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap);
};