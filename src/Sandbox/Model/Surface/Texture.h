#pragma once
#include "Sandbox/Model/Mesh/Geometry/Shader.h"
#include "Sandbox/Model/Mesh/Geometry/Structures.h"

/// @class Texture
/// @brief Texture represents an image that is displayed on the @see Mesh.
class Texture
{
	std::array<Point, 4> _textureAtlasCoords
	{
		Point{0.0f, 0.0f},
		Point{1.0f, 0.0f},
		Point{1.0f, 1.0f},
		Point{0.0f, 1.0f}
	};

	GLuint _texture{};
	const GLenum _textureType = GL_TEXTURE_2D;

	void LoadTexture(const unsigned char* image, const int& width, const int& height);

public:

	/// The constructor that loads a whole image and sets it as a texture.
	/// @param filenameWithImage - Path to the source with image.
	explicit Texture(const std::string& filenameWithImage);

	/// The constructor used to create texture from the <a href="https://en.wikipedia.org/wiki/Texture_atlas">Texture Atlas</a>.
	///	@param filenameWithImage - Path to the source with image.
	///	@param x - The column index of the texture.
	/// @param y - The row index of the texture.
	/// @param spriteSize - The size of the sprite.
	///	@note This constructor is made **exclusively** for the texture atlases. 
	///	If you want to load a simple texture, use the @ref Texture(const std::string&) "Texture(filename)" constructor.
	explicit Texture(const std::string& filenameWithImage, int x, int y, size_t spriteSize);

	/// @brief Texture copy constructor.
	///	@details Used for transferring the existing instance.
	Texture(const Texture&) = default;

	/// @brief Texture move constructor.
	///	@details Used for Texture initialization.
	Texture(Texture&&) = default;

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	/// @brief Sets the UV values of the vertices.
	///	@details Sets the UV values of the vertices, so the texture from the texture atlas could be displayed correctly.
	/// @param vertices - The vertices of the mesh.
	void SetUvToTextureAtlas(std::vector<Vertex>& vertices, bool flip = false) const;

	/// @brief Tells OpenGL to use the texture.
	void Bind(const Shader& shader) const;

	/// @brief Tells OpenGL to stop using this texture.
	void Unbind() const;

	~Texture();
};

