#pragma once
#include "Geometry/Structures.h"
#include "Geometry/Shader.h"
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Application/Sandbox/Camera.h"
#include "Application/Sandbox/Model/Surface/Texture.h"

/// @class Mesh
///	@brief Represents a <a href="https://en.wikipedia.org/wiki/Polygon_mesh" target="_blank">mesh</a> of a @see Model.
class Mesh
{
	VertexArray _vao;
	Shader& _shader;
	GLsizei _indicesAmount{};

public:

	/// @brief The constructor.
	///	@param vertices - The vertices of the mesh.
	/// @param indices - The indices sequence of the vertices position.
	/// @param shader - The shader that the mesh is using.
	Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);

	/// @brief Draws the mesh.
	///	@param origin - A position in the world to place the mesh.
	/// @param texture - The texture to cover the mesh.
	/// @param camera - It is used to bind a shader to see the drawn mesh.
	void Draw(const Position& origin, const Texture& texture, const Camera& camera) const;
};

