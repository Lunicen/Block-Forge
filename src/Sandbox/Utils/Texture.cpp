#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

Texture::Texture(const char* image, GLenum texureType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texureType; //ok
	int widthImg; //ok sprawdzic czy tutaj czy lepiej w .h
	int heightImg; //ok
	int numColCh; //ok

	stbi_set_flip_vertically_on_load(true); //ok
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0); //ok

	glGenTextures(1, &texture); //zmienic id na &texture
	glActiveTexture(slot);
	glBindTexture(texureType, texture);

	//min & mag filters sprawdzic dzialanie
	glTexParameteri(texureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texureType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texureType); //ok

	stbi_image_free(bytes); //ok
	glBindTexture(texureType, 0); //ok
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.GetProgram(), uniform);
	shader.Load();
	glUniform1i(texUni, unit);
}


void Texture::Bind()
{
	glBindTexture(type, texture); //pl
}
void Texture::Delete()
{
	glDeleteTextures(1, &texture);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

