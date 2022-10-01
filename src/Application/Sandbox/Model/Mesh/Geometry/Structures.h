#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/// @brief A 4x4 matrix.
using Matrix = glm::mat4;

/// @brief The group of indexes that represent the indices of the mesh. 
using TriangleIndexes = glm::ivec3;

/// @brief A position of an object.
using Position = glm::ivec3;

/// @brief A point in the 3D space.
using Point3D = glm::vec3;

/// @brief A point in the 2D space.
using Point = glm::vec2;

/// @brief Tells how many vertices a quad (two triangles connected by a hypotenuse) has.
constexpr size_t VerticesInQuad = 4;

/// @brief Represent a single vertex that is used by the shader.
struct Vertex
{
	/// @brief The position of the vertex in the mesh.
	Point3D position;

	/// @brief The texture UV coordinate.
	Point uvCoordinate;
};