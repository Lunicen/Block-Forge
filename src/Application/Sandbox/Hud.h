#pragma once
#include "Model/Mesh/Mesh.h"
#include "Model/Surface/Texture.h"

class Hud
{
public:
	std::vector<Vertex> _vertices;
	std::vector<TriangleIndexes> _indices;

	Shader _shader = Shader("src/Data/Shaders/Hud.vert","src/Data/Shaders/Hud.frag");
	Texture _texture = Texture("src/Data/testHUD.png");
	Mesh _mesh{_vertices, _indices, _shader};

	//std::unique_ptr<Mesh> _mesh = std::make_unique<Mesh>(_vertices, _indices, _shader);
public:
	Hud();

	void Draw();
};

