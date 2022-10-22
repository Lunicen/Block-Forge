#pragma once
#include "Model/Mesh/StaticMesh.h"
#include "Model/Surface/TextureAtlas.h"
class HudItemSlot
{
	Shader& _shader;
	TextureAtlas& _texture;
	Point _position;
	float _scale;
	bool _state;

	std::vector<Vertex> _vertices = {
		Vertex{Point3D{ 0.0f, 0.0f, 0.0f }, Point{ 0.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 0.0f, 0.0f }, Point{ 1.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 1.0f, 0.0f }, Point{1.0f, 1.0f}},
		Vertex{Point3D{ 0.0f, 1.0f, 0.0f }, Point{0.0f, 1.0f}},
	};

	std::vector<TriangleIndexes> _indices =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};

	std::unique_ptr<StaticMesh> _mesh;


public:
	HudItemSlot(TextureAtlas &texture, Shader &shader, Point position, float scale);
	void Activate();
	void Deactivate();
	void Draw();
};

class Hud
{
	TextureAtlas texture = TextureAtlas("src/Data/Textures/HudAtlas.png", 16);
	Shader shader = Shader("src/Data/Shaders/Hud.vert", "src/Data/Shaders/Hud.frag");

	HudItemSlot slot1 = HudItemSlot(texture, shader, Point(-1.0f, -1.0f), 0.25f);

	
	std::vector<std::vector<std::unique_ptr<HudItemSlot>>> HudItemSlotBar;

public:
	Hud();
	void Draw();
};

