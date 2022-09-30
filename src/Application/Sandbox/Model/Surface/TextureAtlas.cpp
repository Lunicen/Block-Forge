#include "TextureAtlas.h"

std::array<Point, 4> TextureAtlas::GetTextureCoordinatesAt(const unsigned x, const unsigned y)
{
	const auto& width = GetWidth();
	const auto& height = GetHeight();

	const auto invertedY = height / _spriteSize - y - 1;

	const std::array<Point, 4> textureCoords = 
	{{
		{
			static_cast<float>(x) * static_cast<float>(_spriteSize) / static_cast<float>(width),
			static_cast<float>(invertedY) * static_cast<float>(_spriteSize) / static_cast<float>(height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(width),
			static_cast<float>(invertedY) * static_cast<float>(_spriteSize) / static_cast<float>(height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(width),
			(static_cast<float>(invertedY) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(height)
		},
		{
			static_cast<float>(x) * static_cast<float>(_spriteSize) / static_cast<float>(width),
			(static_cast<float>(invertedY) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(height)
		}
	}};

	return textureCoords;
}

TextureAtlas::TextureAtlas(const std::string& filenameWithImage, const size_t spriteSize) : Texture(filenameWithImage), _spriteSize(spriteSize)
{
}

void TextureAtlas::SetSprite(std::vector<Vertex>& vertices, const unsigned x, const unsigned y, const bool flip)
{
	const auto& textureCoords = GetTextureCoordinatesAt(x, y); 

	constexpr auto verticesAmount = 4;
	for (auto i = 0; i < verticesAmount; ++i)
	{
		if (flip)
		{
			vertices.at((i + verticesAmount - 1) % verticesAmount).uvCoordinate = textureCoords[i];
		}
		else
		{
			vertices.at(i).uvCoordinate = textureCoords[i];
		}
	}
}

void TextureAtlas::SetSprite(std::array<Point, 4>& textureUvCoordinates, const unsigned x, const unsigned y, const bool flip)
{
	const auto& textureCoords = GetTextureCoordinatesAt(x, y); 

	if (!flip)
	{
		textureUvCoordinates = textureCoords;
		return;
	}

	constexpr auto quadCoordinatesAmount = 4;
	for (auto i = 0; i < quadCoordinatesAmount; ++i)
	{
		textureUvCoordinates[(i + quadCoordinatesAmount - 1) % quadCoordinatesAmount] = textureCoords[i];
	}
}
