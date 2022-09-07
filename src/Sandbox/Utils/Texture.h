#pragma once
#include "Rendering/Shader.h"
#include <glad/glad.h>


/// @class Texture
/// @brief Texture that can be used for objects.
class Texture
{
private:
	GLuint _texture;
	GLenum _type;

public:
#pragma region RuleOfFive
	///@brief constructor
	Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

	/// @brief Texture copy constructor
	///	@details Used for transferring the existing instance.
	Texture(const Texture&) = default;

	/// @brief Texture move constructor.
	///	@details Used for Texture initialization.
	Texture(Texture&&) = default;

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	~Texture();
#pragma endregion

	/// @brief Allows the usage of shader with the texture.
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	/// @brief Tells OpenGL to use the texture.
	void Bind();

	/// @brief Tells OpenGL to stop using this texture.
	void Unbind();

	/// @brief Deletes the texture.
	void Delete();
};

