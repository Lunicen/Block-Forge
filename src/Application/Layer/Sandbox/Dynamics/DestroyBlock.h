#pragma once

#include "../World/Chunks/ChunkUtils.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"

/// @class DestroyBlock
///	@brief The class that destroy blocks
class DestroyBlock {

	public:
		/// @brief Destroy block in front of the camera
		///	@param orientation - orientation of the camera
		///	@param position - position of the camera
		/// @param chunks - the map with chunks with their positions
		///	@param blockMap - block map, which is used to place them inside chunks based on the biome noise.
		static void Destroy(glm::vec3 orientation, glm::vec3 position, HashMap<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap);
};
