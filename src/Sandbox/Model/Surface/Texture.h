#pragma once
#include "Sandbox/Model/Mesh/Geometry/Shader.h"
#include "Sandbox/Model/Mesh/Geometry/Structures.h"

/// @class Texture
/// @brief Texture that can be used for objects.
class Texture
{
	std::array<Point, 4> _coords
	{
		Point{0.0f, 0.0f},
		Point{1.0f, 0.0f},
		Point{1.0f, 1.0f},
		Point{0.0f, 1.0f}
	};

	GLuint _texture{};
	const GLenum _type = GL_TEXTURE_2D;
	std::string _filename;

public:
	explicit Texture(const std::string& filenameWithImage, int x, int y, size_t spriteSize);

	/// @brief Texture copy constructor.
	///	@details Used for transferring the existing instance.
	Texture(const Texture&) = default;

	/// @brief Texture move constructor.
	///	@details Used for Texture initialization.
	Texture(Texture&&) = default;

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	void SetUvVertices(std::vector<Vertex>& vertices) const;

	/// @brief Tells OpenGL to use the texture.
	void Bind(const Shader& shader) const;

	/// @brief Tells OpenGL to stop using this texture.
	void Unbind() const;

	/// @brief Deletes the texture.
	void Delete() const;

	~Texture();
};

