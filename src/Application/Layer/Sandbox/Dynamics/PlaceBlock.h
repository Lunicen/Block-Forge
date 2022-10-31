#pragma once
#include "Application/Layer/Sandbox/World/Chunks/Structure/Chunk.h"


class PlaceBlock {

	float _max_distance = 4.0;



public:
	static void FindBlock();
	static void Place(glm::vec3 _orientation, glm::vec3 _position, std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, BlockMap& blockmap);









};