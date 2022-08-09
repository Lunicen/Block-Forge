#pragma once
#include "Utils/Shader.h"
#include "Utils/ElementBuffer.h"
#include "Utils/VertexArray.h"
#include <glm/gtx/transform.hpp>


class Block
{
	//    5-------6  
	//   /|      /|   
	//  1-------2 | 
	//  | |     | |   
	//  | 4-----|-7  
	//  |/      |/    
	//  0-------3 
	GLfloat _vertices[24] =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
	};

	GLuint _indices[36]
	{
		// bottom
		0, 4, 7,
		7, 3, 0,

		0, 3, 2,

		// top
		2, 6, 5,
		5, 1, 2,

		2, 3, 7,
		7, 4, 5,
		5, 4, 0,

		// reverse
		0, 1, 5,
		5, 6, 7,
		7, 6, 2,
		2, 1, 0
	};

	Shader& _shader;
	glm::mat4 _position{};

	VertexArray _vao;
	VertexBuffer _vbo = VertexBuffer(_vertices, sizeof(_vertices));
	ElementBuffer _ebo = ElementBuffer(_indices, sizeof(_indices));

public:
	Block(int x, int y, int z, Shader& shader);
	void Move(int x, int y, int z);
	void Draw() const;

	Shader GetShader() const;
};

