#include "Hud.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include "Model/Surface/Texture.h"



HudItemSlot::HudItemSlot(TextureAtlas &texture, Shader &shader, Point position, float scale = 1.0f) : _texture(texture), _shader(shader), _position(position), _scale(scale)
{
	for (auto& vertex : _vertices)
	{
		vertex.position = vertex.position * scale;
	}
	
	for (auto& vertex :_vertices)
	{
		vertex.position = vertex.position + Point3D(position.x, position.y, 0);
	}
	
	_texture.SetSprite(_vertices, 1, 0, false);
	_mesh = std::make_unique<StaticMesh>(_vertices, _indices, _shader); //to trzeba zmienic na dynamic mesha
}

void HudItemSlot::Draw()
{
	_mesh->Draw(_position, _texture);
}

void HudItemSlot::Activate() {
	_state = true;
	_texture.SetSprite(_vertices, 1, 0, false);
}

void HudItemSlot::Deactivate() {
	_state = false;
}


Hud::Hud()
{
	float scale = 0.20f;

	//add Row
	HudItemSlotBar.emplace_back(std::vector<std::unique_ptr<HudItemSlot>>());
	HudItemSlotBar.emplace_back(std::vector<std::unique_ptr<HudItemSlot>>());

	//add elements
	/*
	HudItemSlotBar[0].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-1.0f, -1.0f), scale)));
	HudItemSlotBar[0].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.75f, -1.0f), scale)));
	HudItemSlotBar[0].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.5f, -1.0f), scale)));
	HudItemSlotBar[0].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.25f, -1.0f), scale)));
	*/
	//add elements
	/*
	HudItemSlotBar[1].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-1.0f, -0.75f), scale)));
	HudItemSlotBar[1].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.75f, -0.75f), scale)));
	HudItemSlotBar[1].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.5f, -0.75f), scale)));
	HudItemSlotBar[1].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-0.25f, -0.75f), scale)));
	*/
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			HudItemSlotBar[0].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-1.0f + i * scale, -1.0f + j * scale), scale)));
		}
	}


}


void Hud::Draw()
{
	//slot1.Drwa();

	//HudItemSlotBar[0]->Draw();
	//HudItemSlotBar[0]->Draw();

	for (auto& HudItemSlotRow : HudItemSlotBar)
	{
		for (auto& HudItemSlot : HudItemSlotRow)
		{
			HudItemSlot->Draw();
		}
	}
}