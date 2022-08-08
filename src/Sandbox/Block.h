#pragma once
#include "Utils/Shader.h"
#include "Utils/ElementBuffer.h"
#include "Utils/VertexArray.h"
#include <glm/gtx/transform.hpp>


/// @class Block
/// @brief Handles Block existence
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
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,

		 -0.5f, -0.5f, 1.5f,
		 -0.5f, 0.5f, 1.5f,
		 0.5f,  0.5f, 1.5f,
		 0.5f, -0.5f, 1.5f,
	};

	GLuint _indices[36]
	{
		// front
		0, 1, 2,
		2, 3, 0,

		2, 3, 7,
		7, 6, 2,

		1, 2, 5,
		5, 6, 2,

		0, 4, 1,
		1, 5, 4,

		0, 3, 4,
		4, 7, 3,

		4, 7, 5,
		5, 6, 7
	};

	Shader& _shader;
	glm::mat4 _position{};

	VertexArray _vao;
	VertexBuffer _vbo = VertexBuffer(_vertices, sizeof(_vertices));
	ElementBuffer _ebo = ElementBuffer(_indices, sizeof(_indices));

public:
	/// @brief This is a Constructor that allows to create a block.
	/// @param x - X coordinate.
	///	@param y - Y coordinate.
	///	@param z - Z coordinate.
	///	@param shader - Shader that block will use.
	Block(float x, float y, float z, Shader& shader);

	/// @brief This moves block to the x, y, z coordinates.
	/// @param x - X coordinate.
	///	@param y - Y coordinate.
	///	@param z - Z coordinate.
	void Move(float x, float y, float z);

	/// @brief This draws block.
	void Draw() const;

	/// @brief This returns shader that block is using.
	Shader GetShader() const;
};

