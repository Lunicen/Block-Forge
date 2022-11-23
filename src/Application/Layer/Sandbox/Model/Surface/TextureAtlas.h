#pragma once
#include "Texture.h"

/// @class TextureAtlas
/// @brief Represents an image extracted from the <a href="https://en.wikipedia.org/wiki/Texture_atlas">Texture Atlas</a> and used as a Texture.
class TextureAtlas : public Texture
{
	size_t _spriteSize;
	std::array<Point, VerticesInQuad> GetTextureCoordinatesAt(unsigned x, unsigned y);

public:

	/// @brief The constructor.
	///	@param filenameWithImage - Path to the source with image.
	/// @param spriteSize - The size of the sprite.
	explicit TextureAtlas(const std::string& filenameWithImage, size_t spriteSize);

	/// @brief Sets the vertices according to the sprite from the texture atlas.
	///	@param vertices - The vertices of the mesh.
	///	@param x - The column index of the texture.
	/// @param y - The row index of the texture.
	/// @param flip - If true, it flips the texture coordinates 180 degrees.
	void SetSprite(std::vector<Vertex>& vertices, unsigned x, unsigned y, bool flip = false);

	/// @brief Sets the vertices according to the sprite from the texture atlas.
	/// @param vertices - The vertices of the mesh.
	/// @param textureUvCoordinates - textures on the 
	void SetSprite(std::vector<Vertex>& vertices, const std::array<Point, VerticesInQuad>& textureUvCoordinates);

	/// @brief Sets the vertices according to the sprite from the texture atlas.
	///	@param textureUvCoordinates - UV coordinates of a texture.
	///	@param x - The column index of the texture.
	/// @param y - The row index of the texture.
	/// @param flip - If true, it flips the texture coordinates 180 degrees.
	void SetSprite(std::array<Point, VerticesInQuad>& textureUvCoordinates, unsigned x, unsigned y, bool flip = false);
};

