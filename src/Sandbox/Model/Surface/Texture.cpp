#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

#include "Core/EngineExceptions.h"

Texture::Texture(const std::string& filenameWithImage, const int x, const int y, const size_t spriteSize)
{
	constexpr auto slot = GL_TEXTURE0;
	
	auto width = 0;
	auto height = 0;
	auto channelsInFile = 0;

	stbi_set_flip_vertically_on_load(true);
	const auto imageData = stbi_load(filenameWithImage.c_str(), &width, &height, &channelsInFile, 0);

	if (width % spriteSize != 0 || height % spriteSize != 0)
	{
		throw MismatchException("Slot size has wrong size or texture atlas dimensions are incorrect!");
	}

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
	glActiveTexture(slot);
	glBindTexture(_type, _texture);

	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(_type);

	stbi_image_free(imageData);
	glBindTexture(_type, 0);
}

void Texture::SetUvVertices(std::vector<Vertex>& vertices) const
{
	constexpr auto verticesAmount = 4;
	for (auto i = 0; i < verticesAmount; ++i)
	{
		vertices.at(i).uvCoordinate = _coords[i];
	}
}

void Texture::Bind(const Shader& shader) const
{
	const auto textureUniform = glGetUniformLocation(shader.GetProgram(), "textureSample");

	shader.Load();
	glUniform1i(textureUniform, 0);

	glBindTexture(_type, _texture);
}

void Texture::Unbind() const
{
	glBindTexture(_type, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &_texture);
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &_texture);
}
