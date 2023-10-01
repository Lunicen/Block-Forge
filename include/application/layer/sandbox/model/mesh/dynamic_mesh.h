#pragma once
#include "mesh.h"

/// @class DynamicMesh
///	@brief Represents a dynamic <a href="https://en.wikipedia.org/wiki/Polygon_mesh" target="_blank">mesh</a> of a Model.
///	@details Dynamic mesh is a mesh that it's vertices could be changed in a runtime.
///	@note If your object won't change its structure, you should use StaticMesh.
class DynamicMesh final : protected Mesh
{
	std::unique_ptr<VertexBuffer> _vbo;

	Shader& _shader;
	GLsizei _verticesSize;
	GLsizei _indicesInPatternAmount{};
	GLsizei _indicesInOneInstance{};

	std::vector<TriangleIndexes> GenerateIndicesFromPattern(const std::vector<TriangleIndexes>& pattern, const size_t& maxVerticesAmount) const;

public:

	/// @brief The constructor.
	///	@param vertices - The vertices of the mesh.
	/// @param indicesPattern - The indices pattern sequence of the vertices position (to replicate for allocating the buffer).
	/// @param shader - The shader that the mesh is using.
	/// @param maxInstancesAmount - Amount of maximum possible instances to create within this mesh.
	DynamicMesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indicesPattern, Shader& shader, const size_t& maxInstancesAmount);

	/// @brief Rebuilds the mesh.
	///	@param vertices - new mesh vertices.
	void Update(const std::vector<Vertex>& vertices);

	/// @brief Draws the mesh.
	/// @param texture - The texture to cover the mesh.
	/// @param camera - It is used to bind a shader to see the drawn mesh.
	void Draw(const Texture& texture, const Camera& camera);
};

