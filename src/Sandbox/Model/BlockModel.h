#pragma once
#include "BlockFaceModel.h"
#include "Sandbox/Camera.h"

struct BlockFaceMeshes
{
	std::shared_ptr<Mesh> front;
	std::shared_ptr<Mesh> back;
	std::shared_ptr<Mesh> left;
	std::shared_ptr<Mesh> right;
	std::shared_ptr<Mesh> top;
	std::shared_ptr<Mesh> bottom;
};

struct BlockFaceTextures
{
	std::shared_ptr<Texture> front;
	std::shared_ptr<Texture> back;
	std::shared_ptr<Texture> left;
	std::shared_ptr<Texture> right;
	std::shared_ptr<Texture> top;
	std::shared_ptr<Texture> bottom;
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
	BlockFaceMeshes _blockFaces;
	BlockFaceTextures _textures;

public:
	explicit BlockModel(BlockFaceMeshes faces, BlockFaceTextures textures)
		: _blockFaces(std::move(faces)), _textures(std::move(textures))
	{}

	void DrawFront(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_front.DrawAt(origins, camera);
	}

	void DrawBack(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_back.DrawAt(origins, camera);
	}

	void DrawTop(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_top.DrawAt(origins, camera);
	}

	void DrawBottom(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_bottom.DrawAt(origins, camera);
	}

	void DrawLeft(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_left.DrawAt(origins, camera);
	}

	void DrawRight(const std::vector<glm::vec3>& origins, Camera& camera)
	{
		//_right.DrawAt(origins, camera);
	}
};