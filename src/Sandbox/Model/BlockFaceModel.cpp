#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
	: _mesh(std::move(mesh)), _texture(std::move(texture))
{}

void BlockFaceModel::PlaceAt(const std::vector<glm::vec3>& origins) const
{
	std::vector<Matrix> transformations;

	for (auto& origin : origins)
	{
		transformations.emplace_back(translate(glm::mat4(1.0f), origin));
	}

	_mesh->SetTransformations(transformations);
}

void BlockFaceModel::Draw(const Camera& camera) const
{
	_mesh->Draw(*_texture, camera);
}
