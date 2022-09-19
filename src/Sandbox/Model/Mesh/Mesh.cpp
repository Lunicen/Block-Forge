#include "Mesh.h"

#include "Core/EngineExceptions.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader)
	: _shader(shader), _indices(indices), _instancesCreated(0)
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

void Mesh::SetTransformations(const std::vector<Matrix>& transformations)
{
	const auto vbo = VertexBuffer(transformations);

	_vao.Link(vbo, 2, sizeof(Position), 4, 0);
	_vao.Link(vbo, 3, sizeof(Position), 4, 1 * sizeof(Position));
	_vao.Link(vbo, 4, sizeof(Position), 4, 2 * sizeof(Position));
	_vao.Link(vbo, 5, sizeof(Position), 4, 3 * sizeof(Position));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	vbo.Unbind();

	_instancesCreated = transformations.size();
}

void Mesh::Draw(const Texture& texture, const Camera& camera) const
{
	if (_instancesCreated == 0)
	{
		throw UninitializedPropertyAccessException("No instance of this mesh has been created!");
	}

	_shader.Load();
	_vao.Bind();

	texture.Bind(_shader);
	camera.Bind(_shader);

	glDrawElementsInstanced(GL_TRIANGLES,  static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(_instancesCreated));
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
