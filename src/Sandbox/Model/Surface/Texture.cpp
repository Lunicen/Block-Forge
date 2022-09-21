#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

#include "Core/EngineExceptions.h"

Texture::Texture(const std::string& filenameWithImage, const int x, const int y, const size_t spriteSize)
{
	auto width = 0;
	auto height = 0;
	auto channelsInFile = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(filenameWithImage.c_str(), &width, &height, &channelsInFile, 0); // auto?

	_coords = 
	{{
		{
			static_cast<float>(x) * static_cast<float>(spriteSize) / static_cast<float>(width),
			static_cast<float>(y) * static_cast<float>(spriteSize) / static_cast<float>(height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(spriteSize) / static_cast<float>(width),
			static_cast<float>(y) * static_cast<float>(spriteSize) / static_cast<float>(height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(spriteSize) / static_cast<float>(width),
			(static_cast<float>(y) + 1.0f) * static_cast<float>(spriteSize) / static_cast<float>(height)
		},
		{
			static_cast<float>(x) * static_cast<float>(spriteSize) / static_cast<float>(width),
			(static_cast<float>(y) + 1.0f) * static_cast<float>(spriteSize) / static_cast<float>(height)
		}
	}};

	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(_textureType, _texture);

	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_textureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(_textureType);

	stbi_image_free(imageData);
	glBindTexture(_textureType, 0);
}

void Texture::SetUvToTextureAtlas(std::vector<Vertex>& vertices) const
{
	constexpr auto verticesAmount = 4;
	for (auto i = 0; i < verticesAmount; ++i)
	{
		vertices.at(i).uvCoordinate = _coords[i];
	}
}

void Texture::Initialize(const Shader& shader)
{
	const auto textureUniform = glGetUniformLocation(shader.GetProgram(), "textureSample");

	shader.Load();
	glUniform1i(textureUniform, 0);
}

void Texture::Bind() const
{
	glBindTexture(_textureType, _texture);
}

void Texture::Unbind() const
{
	glBindTexture(_textureType, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &_texture);
}

Texture::~Texture()
{
	glBindTexture(_textureType, 0);
	glDeleteTextures(1, &_texture);
}
