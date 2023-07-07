#include "application/layer/sandbox/model/mesh/static_mesh.h"

StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader)
	: _shader(shader)
{
	constexpr auto indexesInOneTriangle = 3;
	_indicesAmount = static_cast<GLsizei>(indices.size()) * indexesInOneTriangle;

	GetVao().Bind();
	const auto vbo = VertexBuffer(vertices);
	const auto ebo = ElementBuffer(indices);

	constexpr auto stride = sizeof(Vertex) / sizeof(float);
	constexpr auto vector2dSize = 2;
	constexpr auto vector3dSize = 3;

	GetVao().Link(vbo, VertexLayout(0, vector3dSize, stride, 0));
	GetVao().Link(vbo, VertexLayout(1, vector2dSize, stride, vector3dSize));

	GetVao().Unbind();
	vbo.Unbind();
	ebo.Unbind();
}



void StaticMesh::Draw(const Position& origin, const Texture& texture, const Camera& camera)
{
	camera.Bind(_shader);

	const auto position = translate(glm::mat4(1.0f), glm::vec3(origin));

	glUniformMatrix4fv(glGetUniformLocation(_shader.GetProgram(), "position"), 1, GL_FALSE, value_ptr(position));

	GetVao().Bind();
	texture.Bind(_shader);

	glDrawElements(GL_TRIANGLES, _indicesAmount, GL_UNSIGNED_INT, nullptr);

	texture.Unbind();
	GetVao().Unbind();
}

void StaticMesh::Draw(const Texture& texture)
{
	_shader.Load();

	GetVao().Bind();
	texture.Bind(_shader);

	glDrawElements(GL_TRIANGLES, _indicesAmount, GL_UNSIGNED_INT, nullptr);

	texture.Unbind();
	GetVao().Unbind();
}


