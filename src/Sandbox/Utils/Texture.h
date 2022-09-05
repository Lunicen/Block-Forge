#pragma once
#include "Rendering/Shader.h"
#include <glad/glad.h>


class Texture
{
public:
	GLuint texture;
	GLenum type;
	Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
	~Texture();
};

