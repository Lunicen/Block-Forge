#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader)
	: _shader(shader)
{
	const auto vbo = VertexBuffer(vertices);
	const auto ebo = ElementBuffer(indices);

	constexpr auto stride = sizeof(Vertex) / sizeof(float);
	constexpr auto vector2dSize = 2;
	constexpr auto vector3dSize = 3;

	_vao.Link(vbo, 0, vector3dSize, stride, 0);
	_vao.Link(vbo, 1, vector2dSize, stride, vector3dSize);

	_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Mesh::SetPositions(const std::vector<Position>& transformations)
{
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
