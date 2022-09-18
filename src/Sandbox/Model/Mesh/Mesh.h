#pragma once
#include "Geometry/Structures.h"
#include "Geometry/Shader.h"
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"


class Mesh
{
	VertexArray _vao;
	Shader& _shader;

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);
	void SetPositions(const std::vector<Position>& transformations);

	void Bind() const;
	void Unbind() const;
};

