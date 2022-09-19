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
