#pragma once
#include <memory>

#include "Mesh/Mesh.h"

/// @class BlockFaceModel
///	@brief Represents face of a @see BlockModel.
class BlockFaceModel
{
	std::array<Point, 4> _textureCoordinates;
	std::shared_ptr<Texture> _texture;

public:

	/// @brief The constructor.
	/// @param uvTextureCoordinates - UV texture coordinates.
	///	@param texture - The texture that the model is covered with.
	BlockFaceModel(std::array<Point, 4> uvTextureCoordinates, std::shared_ptr<Texture> texture);

	std::array<Point, 4>& GetUvCoordinates();
};
