#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core/EngineExceptions.h"

int Texture::_usedTextureSlots = 0;

Texture::Texture(const std::string& filenameWithImage) : _textureSlot(_usedTextureSlots++)
{
	constexpr int maxAvailableTextureSlots = 32;
	if (_usedTextureSlots >= maxAvailableTextureSlots)
	{
		throw BadInitializationException("Cannot create more textures! All available texture slots are used (" + std::to_string(maxAvailableTextureSlots) + ").");
	}

	auto channelsInFile = 0;

	stbi_set_flip_vertically_on_load(true);
	const auto imageData = stbi_load(filenameWithImage.c_str(), &_width, &_height, &channelsInFile, 0);

	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0 + _textureSlot);
	glBindTexture(_textureType, _texture);

	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_textureType, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(_textureType);

	glBindTexture(_textureType, 0);

	stbi_image_free(imageData);
}

void Texture::Bind(const Shader& shader) const
{
	const auto textureUniform = glGetUniformLocation(shader.GetProgram(), "textureSample");

	shader.Load();
	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0 + _textureSlot);
	glBindTexture(_textureType, _texture);
}

void Texture::Unbind() const
{
	glBindTexture(_textureType, 0);
}

Texture::~Texture()
{
	glBindTexture(_textureType, 0);
	glDeleteTextures(1, &_texture);

	--_usedTextureSlots;
}
