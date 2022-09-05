#pragma once
#include "Utils/Shader.h"
#include "Utils/ElementBuffer.h"
#include "Utils/VertexArray.h"
#include "Utils/Texture.h"
#include <glm/gtx/transform.hpp>
#include <stb_image.h>

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
	GLfloat _cubeVertices[120] = {
		//cordinates			//Texture Coordinates

		/*FRONT #face 1*/
		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,

		/*BACK  #face 2*/
		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		/*LEFT  #face 3*/
		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,

		/*RIGHT #face 4*/
		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  		1.0f, 0.0f,

		/*FLOOR #face 5*/
		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  		1.0f, 0.0f,

		/*ROOF  #face 6*/
		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  		1.0f, 0.0f,
	};

	GLuint _cubeIndices[36]
	{
		0,  1,  2,  2,  3,  0,
		4,  5,  6,  6,  7,  4,
		8,  9, 10, 10, 11,  8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	Shader& _shader;
	glm::mat4 _position{};

	VertexArray _vao;
	VertexBuffer _vbo = VertexBuffer(_cubeVertices, sizeof _cubeVertices);
	ElementBuffer _ebo = ElementBuffer(_cubeIndices, sizeof _cubeIndices);

	//TODO tutaj chyba trzeba bedzie dodac dodatkowe zlinkowanie vbo... link/LinkAttrib

	Texture& _texture;

public:
	/// @brief This is a Constructor that allows to create a block.
	/// @param x - X coordinate.
	///	@param y - Y coordinate.
	///	@param z - Z coordinate.
	///	@param shader - Shader that block will use.
	///	@param texture - texture that will be used for the block.
	Block(float x, float y, float z, Shader& shader, Texture& texture);

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

