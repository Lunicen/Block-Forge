#pragma once
#include "Geometry/Structures.h"
#include "Geometry/Shader.h"
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Sandbox/Camera.h"
#include "Sandbox/Model/Surface/Texture.h"

class Mesh
{
	VertexArray _vao;
	Shader& _shader;
	const GLsizei _indicesAmount;

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);
	
	void Draw(const Position& origin, const Texture& texture, const Camera& camera) const;

	void Bind() const;
	void Unbind() const;

	Shader& GetShader() const;
};

