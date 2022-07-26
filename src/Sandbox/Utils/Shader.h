#pragma once
#include <string>
#include "Core/FileUtils.h"
#include "Core/Log.h"
#include <glad/glad.h>

class Shader : protected FileUtils
{
	GLuint program{};
	Log& log = Log::Get();

	std::string GetFileContents(const std::string& filename) const;
	void InitializeProgram(const GLuint& vertexShader, const GLuint& fragmentShader);

public:
	Shader(const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator=(Shader) = delete;
	Shader& operator=(Shader&&) = delete;

	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	void Load() const;
	void Unload() const;

	~Shader();
};

