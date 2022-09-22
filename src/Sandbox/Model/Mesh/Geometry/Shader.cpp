#include "Shader.h"

#include <fstream>
#include <sstream>

std::string Shader::GetFileContents(const std::string& filename) const
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.good())
	{
		_log.Error("The file " + filename + " is corrupted.");
		return "";
	}

	std::string contents;

	file.seekg(0, std::ios::end);
	// ReSharper disable once CppRedundantCastExpression
	contents.resize(static_cast<size_t>(file.tellg()));

	file.seekg(0, std::ios::beg);
	file.read(const_cast<char*>(contents.data()), static_cast<std::streamsize>(contents.size()));

	file.close();
	return contents;
}

void Shader::InitializeProgram(const GLuint& vertexShader, const GLuint& fragmentShader)
{
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
	if (!DoesFileExist(vertexFile))
	{
		_log.Critical("Shader " + vertexFile + " file doesn't exist!");
		return;
	}

	if (!DoesFileExist(fragmentFile))
	{
		_log.Critical("Shader " + fragmentFile + " file doesn't exist!");
		return;
	}

	const auto vertexCode = GetFileContents(vertexFile);
	const auto fragmentCode = GetFileContents(fragmentFile);

	const auto vertexSource = vertexCode.c_str();
	const auto fragmentSource = fragmentCode.c_str();

	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	InitializeProgram(vertexShader, fragmentShader);
}

void Shader::Load() const
{
	glUseProgram(_program);
}

void Shader::Unload() const
{
	glDeleteProgram(_program);
}

GLuint Shader::GetProgram() const
{
	return _program;
}

Shader::~Shader()
{
	Unload();
}
