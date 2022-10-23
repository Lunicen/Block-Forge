#include "Hud.h"
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
	
	_texture.SetSprite(_vertices, 0, 0, false);
	_mesh = std::make_unique<StaticMesh>(_vertices, _indices, _shader); //to trzeba zmienic na dynamic mesha



	for (auto& vertex : _vertices2)
	{
		vertex.position = vertex.position * scale;
	}

	for (auto& vertex : _vertices2)
	{
		vertex.position = vertex.position + Point3D(position.x, position.y, 0);
	}


}

void HudItemSlot::Draw()
{
	_mesh->Draw(_position, _texture);
}

void HudItemSlot::Activate() {
	_state = true;
	_texture.SetSprite(_vertices, 1, 0, false);
	_mesh = std::make_unique<StaticMesh>(_vertices, _indices, _shader);
}

void HudItemSlot::Deactivate() {
	_state = false;
	_texture.SetSprite(_vertices, 0, 0, false);
	_mesh = std::make_unique<StaticMesh>(_vertices, _indices, _shader);
}

void Hud::DeactivateEntireHudItemSlotBar()
{
	for (auto& HudItemSlotRow : HudItemSlotBar)
	{
		for (auto& HudItemSlot : HudItemSlotRow)
		{
			HudItemSlot->Deactivate();
		}
	}
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
		for (int i = 0; i < 10; i++)
		{
			HudItemSlotBar[j].emplace_back(std::move(std::make_unique<HudItemSlot>(texture, shader, Point(-1.0f + i * scale, -1.0f + j * scale), scale)));
		}
	}
	//HudItemSlotBar[0][0]->Activate();
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

void Hud::ChangeSelectedItemSlot(HumanInterfaceDevice &hid)
{
	if (hid.IsPressedOnce(KeyboardKey::key1))
		selectedSlot = 0;
	else if (hid.IsPressedOnce(KeyboardKey::key2))
		selectedSlot = 1;
	else if (hid.IsPressedOnce(KeyboardKey::key3))
		selectedSlot = 2;
	else if (hid.IsPressedOnce(KeyboardKey::key4))
		selectedSlot = 3;
	else if (hid.IsPressedOnce(KeyboardKey::key5))
		selectedSlot = 4;
	else if (hid.IsPressedOnce(KeyboardKey::key6))
		selectedSlot = 5;
	else if (hid.IsPressedOnce(KeyboardKey::key7))
		selectedSlot = 6;
	else if (hid.IsPressedOnce(KeyboardKey::key8))
		selectedSlot = 7;
	else if (hid.IsPressedOnce(KeyboardKey::key9))
		selectedSlot = 8;
	else if (hid.IsPressedOnce(KeyboardKey::key0))
		selectedSlot = 9;
	else if (hid.IsPressedOnce(KeyboardKey::minus))
		selectedRow = 0;
	else if (hid.IsPressedOnce(KeyboardKey::plus))
		selectedRow = 1;
	this->DeactivateEntireHudItemSlotBar();
	HudItemSlotBar[selectedRow][selectedSlot]->Activate();

}
