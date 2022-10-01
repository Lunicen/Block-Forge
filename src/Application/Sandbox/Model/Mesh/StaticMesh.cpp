#include "StaticMesh.h"

StaticMesh::StaticMesh(const std::vector<Point3D>& vertices, const std::vector<TriangleIndexes>& indices,Shader& shader)
	: _shader(shader)
{
	constexpr auto indexesInOneTriangle = 3;
	_indicesAmount = static_cast<GLsizei>(indices.size()) * indexesInOneTriangle;

	_vao.Bind();
	const auto vbo = VertexBuffer(vertices);
	const auto ebo = ElementBuffer(indices);

	constexpr auto stride = sizeof(Point3D) / sizeof(float);
	constexpr auto vector3dSize = 3;

	_vao.Link(vbo, 0, vector3dSize, stride, 0);

	_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader)
	: _shader(shader)
{
	constexpr auto indexesInOneTriangle = 3;
	_indicesAmount = static_cast<GLsizei>(indices.size()) * indexesInOneTriangle;

	_vao.Bind();
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



void StaticMesh::Draw(const Position& origin, const Texture& texture, const Camera& camera) const
{
	camera.Bind(_shader);

	const auto position = translate(glm::mat4(1.0f), glm::vec3(origin));

	glUniformMatrix4fv(glGetUniformLocation(_shader.GetProgram(), "position"), 1, GL_FALSE, value_ptr(position));

	_vao.Bind();
	texture.Bind(_shader);

	glDrawElements(GL_TRIANGLES, _indicesAmount, GL_UNSIGNED_INT, nullptr);

	texture.Unbind();
	_vao.Unbind();
}

void StaticMesh::Draw() const
{
	_shader.Load();

	_vao.Bind();

	glDrawElements(GL_TRIANGLES, _indicesAmount, GL_UNSIGNED_INT, nullptr);

	_vao.Unbind();

}

