#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

Texture::Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	_type = textureType;
	int widthImg;
	int heightImg;
	int numColCh;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &_texture);
	glActiveTexture(slot);
	glBindTexture(textureType, _texture);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(textureType);

	stbi_image_free(bytes);
	glBindTexture(textureType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.GetProgram(), uniform);
	shader.Load();
	glUniform1i(texUni, unit);
}


void Texture::Bind()
{
	glBindTexture(_type, _texture);
}
void Texture::Delete()
{
	glDeleteTextures(1, &_texture);
}

void Texture::Unbind()
{
	glBindTexture(_type, 0);
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &_texture);
}
