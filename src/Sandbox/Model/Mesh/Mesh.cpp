#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader& shader)
	: _vertices(std::move(vertices)), _indices(std::move(indices)), _shader(shader)
{
	_vbo = VertexBuffer(_vertices);
	_ebo = ElementBuffer(_indices);

	constexpr auto stride = sizeof(Vertex) / sizeof(float);
	constexpr auto vector2dSize = 2;
	constexpr auto vector3dSize = 3;

	_vao.Link(_vbo, 0, vector3dSize, stride, 0);
	_vao.Link(_vbo, 1, vector2dSize, stride, vector3dSize);

	_vao.Unbind();
	_vbo.Unbind();
	_ebo.Unbind();
}

void Mesh::Bind() const
{
	_shader.Load();
	_vao.Bind();
}

void Mesh::Unbind() const
{
	_vao.Unbind();
	_shader.Unload();
}

std::vector<Vertex> Mesh::GetVertices() const
{
	return _vertices;
}

std::vector<GLuint> Mesh::GetIndices() const
{
	return _indices;
}

Shader& Mesh::GetShader() const
{
	return _shader;
}
