#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(std::shared_ptr<Mesh> mesh, Texture texture)
	: _mesh(std::move(mesh)), _texture(std::move(texture))
{}

void BlockFaceModel::DrawAt(std::vector<glm::vec3> origins, Camera& camera)
{
}
