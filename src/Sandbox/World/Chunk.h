#pragma once
#include <array>
#include <glm/vec3.hpp>

#include "Sandbox/Block.h"
#include "Sandbox/Camera.h"

constexpr int chunk_size = 3;

class Chunk
{
	enum class Action
	{
		allocateBlocks = 0,
		drawChunk,
		deallocateBlocks
	};

	glm::vec3 _origin{};
	Shader& _blockShader;
	Camera& _camera;

	std::array<
		std::array<
			std::array<Block*, chunk_size>,chunk_size>,chunk_size> _blocks = {{}};

	void IterateThroughChunkAnd(Action actionToDo);

public:
	explicit Chunk(glm::vec3 origin, Shader& blockShader, Camera& camera);

	void Load();
	void Draw();
	void Unload();
};

