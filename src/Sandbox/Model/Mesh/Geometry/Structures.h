#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/// @brief A 4x4 matrix.
typedef glm::mat4 Matrix;

/// @brief The group of indexes that represent the indices of the mesh. 
typedef glm::ivec3 TriangleIndexes;

/// @brief A position in space of the object.
typedef glm::vec3 Position;

/// @brief A point in the 2D space.
typedef glm::vec2 Point;

/// @brief Represent a single vertex that is used by the shader.
struct Vertex
{
	/// @brief The position of the vertex in space.
	Position position;

	/// @brief The texture UV coordinate.
	Point uvCoordinate;
};