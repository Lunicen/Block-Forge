#pragma once
#include <unordered_map>

#include "../World/Chunks/ChunkUtils.h"
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"


class DestroyBlock {

	float _max_distance = 4.0;



	public:
		static void Destroy(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockMap);

};
