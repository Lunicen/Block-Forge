#pragma once
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Geometry/Shader.h"
#include "Geometry/Structures.h"

class Mesh
{
	const std::vector<Vertex> _vertices;
	const std::vector<GLuint> _indices;
	Shader& _shader;

	VertexArray _vao;
	VertexBuffer _vbo;
	ElementBuffer _ebo;

	void Construct();

public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader& shader);
	Mesh(std::vector<Vertex> vertices, Shader& shader);

	void Bind() const;
	void Unbind() const;
};

