#pragma once
#include "Model/Mesh/StaticMesh.h"
#include "Model/Surface/Texture.h"

class Hud
{
public:
	std::vector<Vertex> _vertices = {
		Vertex{Point3D{ 0.0f, 0.0f, 0.0f }, Point{ 0.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 0.0f, 0.0f },Point{ 1.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 1.0f, 0.0f },Point{1.0f, 1.0f}},
		Vertex{Point3D{ 0.0f, 1.0f, 0.0f }, Point{0.0f, 1.0f}},
	};

	std::vector<TriangleIndexes> _indices =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};

	Shader _shader = Shader("src/Data/Shaders/Hud.vert","src/Data/Shaders/Hud.frag");
	Texture _texture = Texture("src/Data/Textures/testHUD.png");
	StaticMesh _mesh{ _vertices, _indices, _shader };

	//std::unique_ptr<Mesh> _mesh = std::make_unique<Mesh>(_vertices, _indices, _shader);
public:
	Hud();


	void Draw();
};

