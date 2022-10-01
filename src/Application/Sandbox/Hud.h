#pragma once
#include "Model/Mesh/StaticMesh.h"
#include "Model/Surface/Texture.h"

class Hud
{
public:
	std::vector<Point3D> _vertices = {
	Point3D(- 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f  ),  //lower left corner
	Point3D(0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f    ), //lower right corner
	Point3D(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f ),  //Upper corner
	Point3D(-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f),    //inner left
	Point3D(0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f ),     //inner right
	Point3D(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f    )    //inner down
	};
	std::vector<TriangleIndexes> _indices = {
	TriangleIndexes(0, 3, 5), //lower left triangle
	TriangleIndexes(3, 2, 4), //lower right triangle
	TriangleIndexes(5, 4, 1)  // Upper triangle
	};

	Shader _shader = Shader("src/Data/Shaders/Hud.vert","src/Data/Shaders/Hud.frag");
	Texture _texture = Texture("src/Data/testHUD.png");
	StaticMesh _mesh{ _vertices, _indices, _shader };

	//std::unique_ptr<Mesh> _mesh = std::make_unique<Mesh>(_vertices, _indices, _shader);
public:
	Hud();

	void Draw();
	void Draw2();
};

