#pragma once
#include <memory>
#include "Mesh/Mesh.h"

class BlockFaceModel
{
	std::unique_ptr<Mesh> _mesh;
	std::shared_ptr<Texture> _texture;

public:
	BlockFaceModel(std::unique_ptr<Mesh>& mesh, std::shared_ptr<Texture> texture);

	void PlaceAt(const std::vector<glm::vec3>& origins, const size_t& chunkSize) const;
	void Draw(const Camera& camera) const;
};
