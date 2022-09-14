#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

Texture::Texture(const std::string& filenameWithImage)
	: _filename(filenameWithImage)
{
	constexpr auto slot = GL_TEXTURE0;
	
	auto width = 0;
	auto height = 0;
	auto channelsInFile = 0;

	stbi_set_flip_vertically_on_load(true);
	const auto bytes = stbi_load(filenameWithImage.c_str(), &width, &height, &channelsInFile, 0);

	glGenTextures(1, &_texture);
	glActiveTexture(slot);
	glBindTexture(_type, _texture);

	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(_type);

	stbi_image_free(bytes);
	glBindTexture(_type, 0);
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
