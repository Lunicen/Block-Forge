#pragma once
#include "Mesh.h"

class DynamicMesh final : protected Mesh
{
	Shader& _shader;
	std::vector<Vertex> _vertices;
	GLsizei _indicesInPatternAmount{};
	GLsizei _indicesInOneInstance{};

	std::vector<TriangleIndexes> GenerateIndicesFromPattern(const std::vector<TriangleIndexes>& pattern, const size_t& maxVerticesAmount) const;

public:

	/// @brief The constructor.
	///	@param vertices - The vertices of the mesh.
	/// @param indicesPattern - The indices pattern sequence of the vertices position (to replicate for allocating the buffer).
	/// @param shader - The shader that the mesh is using.
	DynamicMesh(std::vector<Vertex> vertices, const std::vector<TriangleIndexes>& indicesPattern, Shader& shader, const size_t& maxInstancesAmount);

	void Update(const std::vector<Vertex>& vertices);

	/// @brief Draws the mesh.
	/// @param texture - The texture to cover the mesh.
	/// @param camera - It is used to bind a shader to see the drawn mesh.
	void Draw(const Texture& texture, const Camera& camera) const;
};

