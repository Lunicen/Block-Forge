#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& filenameWithImage, size_t spriteSize) : Texture(filenameWithImage), _spriteSize(spriteSize)
{
}

void TextureAtlas::SetSprite(std::vector<Vertex>& vertices, const unsigned x, const unsigned y, const bool flip) const
{
	const auto invertedY = _height / _spriteSize - y - 1;

	const std::array<Point, 4> textureCoords = 
	{{
		{
			static_cast<float>(x) * static_cast<float>(_spriteSize) / static_cast<float>(_width),
			static_cast<float>(invertedY) * static_cast<float>(_spriteSize) / static_cast<float>(_height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(_width),
			static_cast<float>(invertedY) * static_cast<float>(_spriteSize) / static_cast<float>(_height)
		},
		{
			(static_cast<float>(x) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(_width),
			(static_cast<float>(invertedY) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(_height)
		},
		{
			static_cast<float>(x) * static_cast<float>(_spriteSize) / static_cast<float>(_width),
			(static_cast<float>(invertedY) + 1.0f) * static_cast<float>(_spriteSize) / static_cast<float>(_height)
		}
	}};

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
