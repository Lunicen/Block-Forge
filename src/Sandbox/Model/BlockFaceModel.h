#pragma once
#include <memory>
#include "Mesh/Mesh.h"

class BlockFaceModel
{
	std::unique_ptr<Mesh> _mesh;
	std::shared_ptr<Texture> _texture;

public:
	BlockFaceModel(std::unique_ptr<Mesh>& mesh, std::shared_ptr<Texture> texture);
	
	void Draw(const Position& origin, const Camera& camera) const;
};
