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

	const size_t _indicesAmount;
	size_t _instancesCreated;

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<TriangleIndexes>& indices, Shader& shader);
	void SetTransformations(const std::vector<Matrix>& transformations);
	
	void Draw(const Texture& texture, const Camera& camera) const;
	void DrawAt(const glm::vec3& origin, const Texture& texture, const Camera& camera) const;

	void Bind() const;
	void Unbind() const;

	Shader& GetShader() const;
};

