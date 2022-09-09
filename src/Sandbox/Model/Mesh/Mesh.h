#pragma once
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Geometry/Shader.h"

class Mesh
{
	const std::vector<Vertex> _vertices;
	const std::vector<GLuint> _indices;
	Shader& _shader;

	VertexArray _vao;
	VertexBuffer _vbo;
	ElementBuffer _ebo;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader& shader);

	void Bind() const;
	void Unbind() const;

	std::vector<Vertex> GetVertices() const;
	std::vector<GLuint> GetIndices() const;
	Shader& GetShader() const;
};

