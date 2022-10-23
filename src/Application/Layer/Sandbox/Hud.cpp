#include "Hud.h"
#include "Model/Surface/Texture.h"

HudItemSlot::HudItemSlot(TextureAtlas &texture, Shader &shader, const Point position, const float scale = 1.0f)
: _shader(shader), _texture(texture), _position(position), _scale(scale), _state(false)
{
	for (auto& vertex : _vertices)
	{
		vertex.position = vertex.position * _scale;
	}
	
	for (auto& vertex :_vertices)
	{
		vertex.position = vertex.position + Point3D(_position.x, _position.y, 0);
	}
	
	_texture.SetSprite(_vertices, 0, 0, false);
	_mesh = std::make_unique<StaticMesh>(_vertices, _indices, _shader);

	for (auto& vertex : _vertices2)
	{
		vertex.position = vertex.position * _scale;
	}

	for (auto& vertex : _vertices2)
	{
		vertex.position = vertex.position + Point3D(_position.x, _position.y, 0);
	}


}

void HudItemSlot::Draw() const
{
	_mesh->Draw(_texture);
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

void Hud::DeactivateEntireHudItemSlotBar() const
{
	for (auto& hudItemSlotRow : _hudItemSlotBar)
	{
		for (auto& hudItemSlot : hudItemSlotRow)
		{
			hudItemSlot->Deactivate();
		}
	}
}

Hud::Hud()
{
	float scale = 0.20f;
	constexpr int numberOfColumns = 2;
	// ReSharper disable once CppTooWideScope
	constexpr int numberOfRows = 10;

	_hudItemSlotBar.emplace_back(std::vector<std::unique_ptr<HudItemSlot>>{});
	_hudItemSlotBar.emplace_back(std::vector<std::unique_ptr<HudItemSlot>>{});



	for (int column = 0; column < numberOfColumns; column++)
	{

		for (int row = 0; row < numberOfRows; row++)
		{
			_hudItemSlotBar[column].emplace_back(std::make_unique<HudItemSlot>(_texture, _shader, Point(-1.0f + static_cast<float>(row) * scale, -1.0f + static_cast<float>(column) * scale), scale));
		}
	}
}

void Hud::Draw() const
{
	for (auto& hudItemSlotRow : _hudItemSlotBar)
	{
		for (const auto& hudItemSlot : hudItemSlotRow)
		{
			hudItemSlot->Draw();
		}
	}
}

void Hud::ChangeSelectedItemSlot(HumanInterfaceDevice &hid)
{
	if (hid.IsPressedOnce(KeyboardKey::key1))	_selectedSlot = 0;
	else if (hid.IsPressedOnce(KeyboardKey::key2))	_selectedSlot = 1;
	else if (hid.IsPressedOnce(KeyboardKey::key3))	_selectedSlot = 2;
	else if (hid.IsPressedOnce(KeyboardKey::key4))	_selectedSlot = 3;
	else if (hid.IsPressedOnce(KeyboardKey::key5))	_selectedSlot = 4;
	else if (hid.IsPressedOnce(KeyboardKey::key6))	_selectedSlot = 5;
	else if (hid.IsPressedOnce(KeyboardKey::key7))	_selectedSlot = 6;
	else if (hid.IsPressedOnce(KeyboardKey::key8))	_selectedSlot = 7;
	else if (hid.IsPressedOnce(KeyboardKey::key9))	_selectedSlot = 8;
	else if (hid.IsPressedOnce(KeyboardKey::key0))	_selectedSlot = 9;

	else if (hid.IsPressedOnce(KeyboardKey::minus))	_selectedRow = 0;
	else if (hid.IsPressedOnce(KeyboardKey::plus))	_selectedRow = 1;

	else
	{
		//do nothing
	}

	this->DeactivateEntireHudItemSlotBar();
	_hudItemSlotBar[_selectedRow][_selectedSlot]->Activate();

}
