#pragma once
#include "BlockFaceModel.h"
#include "Sandbox/Camera.h"

struct BlockFaces
{
	BlockFaceModel front;
	BlockFaceModel back;
	BlockFaceModel left;
	BlockFaceModel right;
	BlockFaceModel top;
	BlockFaceModel bottom;
};

struct FacesVisibility
{
	bool front;
	bool back;
	bool left;
	bool right;
	bool top;
	bool bottom;
};

class BlockModel
{
	BlockFaces _blockFaces;

public:
	explicit BlockModel(BlockFaces faces)
		: _blockFaces(std::move(faces))
	{}

	void DrawFrontFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.front.Draw(origin, camera);
	}

	void DrawBackFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.back.Draw(origin, camera);
	}
	
	void DrawLeftFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.left.Draw(origin, camera);
	}

	void DrawRightFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.right.Draw(origin, camera);
	}

	void DrawTopFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.top.Draw(origin, camera);
	}

	void DrawBottomFace(const Position& origin, const Camera& camera) const
	{
		_blockFaces.bottom.Draw(origin, camera);
	}
};