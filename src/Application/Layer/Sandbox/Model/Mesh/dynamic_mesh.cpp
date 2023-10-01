#include "application/layer/sandbox/model/mesh/dynamic_mesh.h"

#include "application/layer/sandbox/world/biomes/biome.h"

std::vector<TriangleIndexes> DynamicMesh::GenerateIndicesFromPattern(const std::vector<TriangleIndexes>& pattern, const size_t& maxVerticesAmount) const
{
	std::vector<TriangleIndexes> indices;
	for (size_t i = 0; i < maxVerticesAmount; ++i)
	{
		const auto& multiplier = i * _indicesInOneInstance;

		constexpr auto indicesInOneTriangle = 3;
		for (auto j = 0; j < _indicesInPatternAmount / indicesInOneTriangle; ++j)
		{
			indices.emplace_back(pattern[j] + static_cast<int>(multiplier));
		}
	}

	return indices;
}

DynamicMesh::DynamicMesh(
	const std::vector<Vertex>& vertices,
	const std::vector<TriangleIndexes>& indicesPattern,
	Shader& shader, 
	const size_t& maxInstancesAmount) : _shader(shader), _verticesSize(static_cast<GLsizei>(vertices.size()))
{
	constexpr auto indexesInOneTriangle = 3;
	_indicesInPatternAmount = static_cast<GLsizei>(indicesPattern.size()) * indexesInOneTriangle;

	const auto& triangleWithMaxValue = std::max_element(indicesPattern.begin(), indicesPattern.end(),
    [](const TriangleIndexes& a, const TriangleIndexes& b)
    {
        return std::max({ a.x, a.y, a.z }) < std::max({ b.x, b.y, b.z });
    });
	_indicesInOneInstance = std::max({triangleWithMaxValue->x, triangleWithMaxValue->y, triangleWithMaxValue->z}) + 1;

	const auto& indices = GenerateIndicesFromPattern(indicesPattern, maxInstancesAmount);

	GetVao().Bind();
	_vbo = std::make_unique<VertexBuffer>(sizeof(Vertex), maxInstancesAmount * _indicesInOneInstance);
	const auto ebo = ElementBuffer(indices);

	constexpr auto stride = sizeof(Vertex) / sizeof(float);
	constexpr auto vector2dSize = 2;
	constexpr auto vector3dSize = 3;

	GetVao().Link(*_vbo, VertexLayout(0, vector3dSize, stride, 0));
	GetVao().Link(*_vbo, VertexLayout(1, vector2dSize, stride, vector3dSize));

	GetVao().Unbind();
	_vbo->Unbind();
	ebo.Unbind();

	_vbo->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(vertices.size()) * static_cast<GLsizeiptr>(sizeof(Vertex)), vertices.data());
	_vbo->Unbind();
}

void DynamicMesh::Update(const std::vector<Vertex>& vertices)
{
	if (vertices.empty() && _verticesSize == 0) return;

	_verticesSize = static_cast<GLsizei>(vertices.size());

	_vbo->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(vertices.size()) * static_cast<GLsizeiptr>(sizeof(Vertex)), vertices.data());
	_vbo->Unbind();
}

void DynamicMesh::Draw(const Texture& texture, const Camera& camera)
{
	if (_verticesSize == 0) return;

	camera.Bind(_shader);

	GetVao().Bind();
	texture.Bind(_shader);
	glDrawElements(GL_TRIANGLES, _verticesSize / _indicesInOneInstance * _indicesInPatternAmount, GL_UNSIGNED_INT, nullptr);
	texture.Unbind();
	GetVao().Unbind();
}
