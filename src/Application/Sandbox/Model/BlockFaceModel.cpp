#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(std::array<Point, 4> uvTextureCoordinates)
{
	_textureCoordinates = std::move(uvTextureCoordinates);
}

std::array<Point, 4>& BlockFaceModel::GetUvCoordinates()
{
	return _textureCoordinates;
}
