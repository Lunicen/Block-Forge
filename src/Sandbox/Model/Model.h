#pragma once
#include "Mesh/Mesh.h"
#include "Mesh/Surface/Texture.h"
#include "Sandbox/Camera.h"

class Model
{
	std::unique_ptr<Mesh> _mesh;
	Texture _texture;
	Camera _camera;

public:
	Model(const Mesh& mesh, Texture texture, const Camera& camera);

	void Draw(glm::vec3 origin) const;
	//void Draw(std::vector<glm::vec3> origins);
};

