#include "application/layer/sandbox/model/block_model.h"

BlockFaceModel::BlockFaceModel(const std::array<Point, VerticesInQuad>& uvTextureCoordinates) : _textureCoordinates(uvTextureCoordinates){}

[[nodiscard]] std::array<Point, VerticesInQuad>& BlockFaceModel::GetUvCoordinates()
{
	return _textureCoordinates;
}

