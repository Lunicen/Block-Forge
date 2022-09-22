#include "BlockFaceModel.h"


BlockFaceModel::BlockFaceModel(std::unique_ptr<Mesh>& mesh, std::shared_ptr<Texture> texture)
	: _mesh(std::move(mesh)), _texture(std::move(texture))
{}

void BlockFaceModel::Draw(const glm::vec3& origin, const Camera& camera) const
{
	_mesh->Draw(origin, *_texture, camera);
}
