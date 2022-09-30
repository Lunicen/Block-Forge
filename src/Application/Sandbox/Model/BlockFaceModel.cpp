#include "BlockFaceModel.h"

BlockFaceModel::BlockFaceModel(const std::array<Point, 4>& uvTextureCoordinates)
{
	_textureCoordinates = uvTextureCoordinates;
}

std::array<Point, 4>& BlockFaceModel::GetUvCoordinates()
{
	return _textureCoordinates;
}
