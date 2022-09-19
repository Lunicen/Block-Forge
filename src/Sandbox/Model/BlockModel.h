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

	void Draw(const Camera& camera) const
	{
		_blockFaces.front.Draw(camera);
		_blockFaces.back.Draw(camera);
		_blockFaces.left.Draw(camera);
		_blockFaces.right.Draw(camera);
		_blockFaces.top.Draw(camera);
		_blockFaces.bottom.Draw(camera);
	}

	void SetFrontFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.front.PlaceAt(origins);
	}

	void SetBackFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.back.PlaceAt(origins);
	}
	
	void SetLeftFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.left.PlaceAt(origins);
	}

	void SetRightFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.right.PlaceAt(origins);
	}

	void SetTopFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.top.PlaceAt(origins);
	}

	void SetBottomFaces(const std::vector<glm::vec3>& origins) const
	{
		_blockFaces.bottom.PlaceAt(origins);
	}
};