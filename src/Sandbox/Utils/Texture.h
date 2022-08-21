#pragma once
#include "Shader.h"
#include <glad/glad.h>


class Texture
{

public:
	//GLuint ID; //zapytac huberta na co zmienic id (pewnie na funkcje do pobierania tej rzeczy)
	GLuint texture; //sprawdzic czy tak moze byc zamiast tego
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit); //czy shader musi byc podany jako referencja?
	void Bind();
	void Unbind();
	void Delete();
	
};

