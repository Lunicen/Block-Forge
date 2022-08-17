#include "Texture.h"
/*
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	
	type = texType;

	int widthImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);


	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);


	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);


	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.GetProgram(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Load();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}


void Texture::Bind()
{
	glBindTexture(type, ID);
}
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}
*/