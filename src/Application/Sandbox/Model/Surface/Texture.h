#pragma once
#include "Application/Sandbox/Model/Mesh/Geometry/Shader.h"
#include "Application/Sandbox/Model/Mesh/Geometry/Structures.h"

/// @class Texture
/// @brief Texture represents an image that is displayed on the @see Mesh.
class Texture
{
	static int _usedTextureSlots;
	
	GLuint _texture{};
	int _textureSlot{};
	
	const GLenum _textureType = GL_TEXTURE_2D;

	int _height = 0;
	int _width = 0;

public:

	/// The constructor that loads a whole image and sets it as a texture.
	/// @param filenameWithImage - Path to the source with image.
	explicit Texture(const std::string& filenameWithImage);

	/// @brief Texture copy constructor.
	///	@details Used for transferring the existing instance.
	Texture(const Texture&) = default;

	/// @brief Texture move constructor.
	///	@details Used for Texture initialization.
	Texture(Texture&&) = default;

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	/// @brief Tells OpenGL to use the texture.
	void Bind(const Shader& shader) const;

	/// @brief Tells OpenGL to stop using this texture.
	void Unbind() const;

	/// @brief Returns image height.
	int& GetHeight();

	/// @brief Returns image width.
	int& GetWidth();

	~Texture();
};

