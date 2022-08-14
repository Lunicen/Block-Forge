#pragma once
#include <string>
#include "Core/FileUtils.h"
#include "Core/Log.h"
#include <glad/glad.h>

/// @class Shader
/// @brief Handles shader programs
/// @details The shader programs that are handled by this class
/// are required to be written in the GLSL language.
///	The recommended practice is to use `.vert` extension for the vertex shader file
///	and `.frag` for the fragment shader files.
class Shader : protected FileUtils
{
	GLuint _program{};
	Log& _log = Log::Get();

	std::string GetFileContents(const std::string& filename) const;
	void InitializeProgram(const GLuint& vertexShader, const GLuint& fragmentShader);

public:

	/// @brief Shader copy constructor
	///	@details Used for transferring the existing instance.
	Shader(const Shader&) = default;

	/// @brief Shader move constructor.
	///	@details Used for Shader initialization.
	Shader(Shader&&) = default;

	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&&) = delete;

	/// @brief Shader constructor.
	///	@details The constructor takes the shader files and translates them to the readable format.
	/// That way the operations like loading or unloading shaders could be made rapidly.
	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	/// @brief Tells OpenGL to use the shader program.
	void Load() const;

	/// @brief Tells OpenGL to stop using this shader program.
	void Unload() const;

	/// @brief Returns the shader program.
	GLuint GetProgram() const;

	~Shader();
};

