#pragma once
#include "BlockFaceModel.h"

class BlockModel
{
	BlockFaceModel _front;
	BlockFaceModel _back;
	BlockFaceModel _left;
	BlockFaceModel _right;
	BlockFaceModel _top;
	BlockFaceModel _bottom;

public:
	explicit BlockModel(const std::array<BlockFaceModel, 6>& blockFaces)
		: _front(blockFaces[0]), _back(blockFaces[1]),
		  _left(blockFaces[2]), _right(blockFaces[3]),
		  _top(blockFaces[4]), _bottom(blockFaces[5])
	{}

	void DrawFront(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_front.DrawAt(origins, camera);
	}

	void DrawBack(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_back.DrawAt(origins, camera);
	}

	void DrawTop(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_top.DrawAt(origins, camera);
	}

	void DrawBottom(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_bottom.DrawAt(origins, camera);
	}

	void DrawLeft(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_left.DrawAt(origins, camera);
	}

	void DrawRight(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		_right.DrawAt(origins, camera);
	}
};