#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

Texture::Texture(const char* image, const GLenum textureType, const GLenum slot, const GLenum format, const GLenum pixelType) : _type(textureType)
{
	int widthImg = 0;
	int heightImg = 0;
	int numColCh = 0;

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

// ReSharper disable once CppMemberFunctionMayBeStatic
void Texture::TexUnit(const Shader& shader) const
{
	const auto textureUniform = glGetUniformLocation(shader.GetProgram(), "tex0");

	shader.Load();
	glUniform1i(textureUniform, 0);
}

void Texture::Bind() const
{
	glBindTexture(_type, _texture);
}
void Texture::Delete() const
{
	glDeleteTextures(1, &_texture);
}

void Texture::Unbind() const
{
	glBindTexture(_type, 0);
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &_texture);
}
