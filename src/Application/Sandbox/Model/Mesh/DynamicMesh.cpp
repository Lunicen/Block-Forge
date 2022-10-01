#include "DynamicMesh.h"

#include "Application/Sandbox/World/Biomes/Biome.h"

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
	std::vector<Vertex> vertices,
	const std::vector<TriangleIndexes>& indicesPattern,
	Shader& shader, 
	const size_t& maxInstancesAmount) : _shader(shader), _vertices(std::move(vertices))
{
	constexpr auto indexesInOneTriangle = 3;
	_indicesInPatternAmount = static_cast<GLsizei>(indicesPattern.size()) * indexesInOneTriangle;

	const auto& triangleWithMaxValue = std::max_element(
		indicesPattern.begin(), 
		indicesPattern.end(),
		[](const TriangleIndexes &a, const TriangleIndexes &b)
		{
			return std::max({a.x, a.y, a.z}) < std::max({b.x, b.y, b.z});
		}
	);
	_indicesInOneInstance = std::max({triangleWithMaxValue->x, triangleWithMaxValue->y, triangleWithMaxValue->z}) + 1;

	const auto& indices = GenerateIndicesFromPattern(indicesPattern, maxInstancesAmount);

	_vao.Bind();
	_vbo = std::make_unique<VertexBuffer>(sizeof(Vertex), maxInstancesAmount * _indicesInOneInstance);
	const auto ebo = ElementBuffer(indices);

	constexpr auto stride = sizeof(Vertex) / sizeof(float);
	constexpr auto vector2dSize = 2;
	constexpr auto vector3dSize = 3;

	_vao.Link(*_vbo, 0, vector3dSize, stride, 0);
	_vao.Link(*_vbo, 1, vector2dSize, stride, vector3dSize);

	_vao.Unbind();
	_vbo->Unbind();
	ebo.Unbind();
}

void DynamicMesh::Update(const std::vector<Vertex>& vertices)
{
	_vertices = vertices;

	_vbo->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(_vertices.size()) * static_cast<GLsizeiptr>(sizeof(Vertex)), _vertices.data());
	_vbo->Unbind();
}

void DynamicMesh::Draw(const Texture& texture, const Camera& camera) const
{
	if (_vertices.empty()) return;

	camera.Bind(_shader);

	_vao.Bind();
	texture.Bind(_shader);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_vertices.size()) / _indicesInOneInstance * _indicesInPatternAmount, GL_UNSIGNED_INT, nullptr);
	texture.Unbind();
	_vao.Unbind();
}
