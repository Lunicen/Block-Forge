#pragma once
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"


class PlaceBlock {

public:
	static void Place(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockmap);
};