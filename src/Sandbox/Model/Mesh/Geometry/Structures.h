#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

typedef glm::mat4 Matrix;
typedef glm::ivec3 TriangleIndexes;
typedef glm::vec3 Position;
typedef glm::vec2 Point;
struct Vertex
{
	Position position;
	Point uvCoordinate;
};