#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(std::array<Point, 4> uvTextureCoordinates, std::shared_ptr<Texture> texture)
{
	_textureCoordinates = std::move(uvTextureCoordinates);
	_texture = std::move(texture);
}

std::array<Point, 4>& BlockFaceModel::GetUvCoordinates()
{
	return _textureCoordinates;
}
