#pragma once
#include "Mesh.h"

/// @class StaticMesh
///	@brief Represents a static <a href="https://en.wikipedia.org/wiki/Polygon_mesh" target="_blank">mesh</a> of a Model.
///	@details Static mesh is a mesh that it's vertices will never change.
class StaticMesh final : protected Mesh
{
	Shader& _shader;
	GLsizei _indicesAmount{};

public:

	StaticMesh(const std::vector<Point3D>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);
	/// @brief The constructor.
	///	@param vertices - The vertices of the mesh.
	/// @param indices - The indices sequence of the vertices position.
	/// @param shader - The shader that the mesh is using.
	StaticMesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);

	/// @brief Draws the mesh.
	///	@param origin - A position in the world to place the mesh.
	/// @param texture - The texture to cover the mesh.
	/// @param camera - It is used to bind a shader to see the drawn mesh.
	void Draw(const Position& origin, const Texture& texture, const Camera& camera);


	/// @brief Draws the mesh
	/// @param texture - The texture to cover the mesh.
	void Draw(const Texture& texture);



	void Draw();
};

