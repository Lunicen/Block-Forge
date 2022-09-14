#pragma once
#include <memory>
#include "Sandbox/Camera.h"
#include "Surface/Texture.h"
#include "Mesh/Mesh.h"

class BlockFaceModel
{
	std::shared_ptr<Mesh> _mesh;
	Texture _texture;

	/*std::array<GLfloat, 8> _textureVertices
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};*/

public:
	BlockFaceModel(std::shared_ptr<Mesh> mesh, Texture texture);

	void DrawAt(std::vector<glm::vec3> origins, Camera& camera);
};
