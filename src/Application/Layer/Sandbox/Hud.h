#pragma once
#include "Model/Mesh/StaticMesh.h"
#include "Model/Mesh/DynamicMesh.h"
#include "Model/Surface/TextureAtlas.h"
#include "World/Blocks/BlockMap.h"

/// @class HudItemSlot
/// @brief An item slot to hold a block or item in hud or players inventory on screen.
class HudItemSlot
{
	Shader& _shader;
	TextureAtlas& _texture;
	TextureAtlas& _itemTexture;
	Point _position;
	float _scale;
	bool _state;
	bool _isContainingItem;
	//zmienna do przechowywania bloku, bedzie potem na podstawie tego mozna zobaczyc co postawic
	BlockMap& _blockMap;
	std::string _item;

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

	std::vector<Vertex> _vertices2 = {
		Vertex{Point3D{ 0.0f, 0.0f, 0.0f }, Point{ 0.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 0.0f, 0.0f }, Point{ 1.0f, 0.0f}},
		Vertex{Point3D{ 1.0f, 1.0f, 0.0f }, Point{1.0f, 1.0f}},
		Vertex{Point3D{ 0.0f, 1.0f, 0.0f }, Point{0.0f, 1.0f}},
	};

	std::vector<TriangleIndexes> _indices2 =
	{
		TriangleIndexes{0, 1, 2},
		TriangleIndexes{2, 3, 0}
	};

	std::unique_ptr<StaticMesh> _mesh2;


public:
	/// @brief Constructor that creates item slot in Hud.
	///	@param blockMap - texture Atlas for blocks.
	///	@param texture - Texture Atlas with 2 textures (selected and passive) for the item slot.
	///	@param itemTexture - Texture Atlas with item held in the item slot.
	///	@param shader - shader used for item slot.
	///	@param position - position of the item slot.
	/// @param scale - scale of the item slot.
	HudItemSlot(BlockMap& blockMap, TextureAtlas& texture, TextureAtlas &itemTexture, Shader &shader, Point position, float scale);

	/// @brief Function Selects slot and changes it's texture.
	void Activate();

	/// @brief Function deselects slot and changes it's texture.
	void Deactivate();

	/// @brief Function that adds item to currently held slot.
	void AddItem(std::string block);

	/// @brief Function that adds item to currently held slot.
	void RemoveItem();

	/// @brief Function that returns item to currently held slot.
	std::string GetItem() const;

	/// @brief Function draws item slot on screen.
	void Draw() const;
};

/// @class Hud
/// @brief Hud that contains other hud subelements (example: Hud Item slot), allows them to be drawn.
class Hud
{
	TextureAtlas _texture = TextureAtlas("src/Data/Textures/HudAtlas.png", 16);
	TextureAtlas _fullGameAtlas = TextureAtlas("src/Data/Textures/FullGameAtlas.png", 16);

	Shader _shader = Shader("src/Data/Shaders/Hud.vert", "src/Data/Shaders/Hud.frag");
	std::vector<std::vector<std::unique_ptr<HudItemSlot>>> _hudItemSlotBar;
	int _selectedRow = 0;
	int _selectedSlot = 0;
	void DeactivateEntireHudItemSlotBar() const;

public:

	/// @brief Constructor that creates Hud.
	Hud(BlockMap& blockMap);

	/// @brief Function that Draws Hud on screen.
	void Draw() const;

	/// @brief Function that changes selected item slot based on button pressed by user.
	///	@param hid - Reference to the Human Interface Device. 
	void ChangeSelectedItemSlot(HumanInterfaceDevice &hid);


	/// @brief Function that returns item currently held in players hand.
	std::string GetHeldItem();
};

