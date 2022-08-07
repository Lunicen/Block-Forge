#pragma once
#include "Utils/Shader.h"
#include "Utils/ElementBuffer.h"
#include "Utils/VertexArray.h"
#include <GLFW/glfw3.h>


class Block
{
	private:

		//    5-------6  
		//   /|      /|   
		//  1-------2 | 
		//  | |     | |   
		//  | 4-----|-7  
		//  |/      |/    
		//  0-------3 
		GLfloat vertices[24] =
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

		GLuint indices[36]
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

		float x;
		float y;
		float z;
		VertexArray vao;


public:
	Block(float x, float y, float z);
	void Move(float x, float y, float z);
	void Draw();
};

