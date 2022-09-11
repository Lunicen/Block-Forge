#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(const std::shared_ptr<Mesh> mesh, const Texture& texture)
	: _mesh(mesh), _texture(texture)
{}

void BlockFaceModel::DrawAt(std::vector<glm::vec3> origins, Camera& camera)
{
}
