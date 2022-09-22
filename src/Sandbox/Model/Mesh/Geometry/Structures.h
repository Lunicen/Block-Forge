#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/// @brief A 4x4 matrix.
using Matrix = glm::mat4;

/// @brief The group of indexes that represent the indices of the mesh. 
using TriangleIndexes = glm::ivec3;

/// @brief A position in space of the object.
using Position = glm::vec3;

/// @brief A point in the 2D space.
using Point = glm::vec2;

/// @brief Represent a single vertex that is used by the shader.
struct Vertex
{
	/// @brief The position of the vertex in space.
	Position position;

	/// @brief The texture UV coordinate.
	Point uvCoordinate;
};