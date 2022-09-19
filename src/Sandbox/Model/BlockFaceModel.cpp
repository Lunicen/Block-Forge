#include "BlockFaceModel.h"

#include "Sandbox/World/Chunks/ChunkUtils.h"

BlockFaceModel::BlockFaceModel(std::unique_ptr<Mesh>& mesh, std::shared_ptr<Texture> texture)
	: _mesh(std::move(mesh)), _texture(std::move(texture))
{}

void BlockFaceModel::PlaceAt(const std::vector<glm::vec3>& origins, const size_t& chunkSize) const
{
	std::vector<Matrix> transformations;
	const auto midpoint = ChunkUtils::CalculateMidPoint(chunkSize);

	transformations.reserve(origins.size());
	for (auto& origin : origins)
	{
		const auto normalizedOrigin = origin - glm::vec3(midpoint, midpoint, midpoint);
		transformations.emplace_back(translate(glm::mat4(1.0f), normalizedOrigin));
	}

	_mesh->SetTransformations(transformations);
}

void BlockFaceModel::Draw(const Camera& camera) const
{
	_mesh->Draw(*_texture, camera);
}
