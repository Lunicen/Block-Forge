#pragma once
#include <memory>

#include "Mesh/Mesh.h"

/// @class BlockFaceModel
///	@brief Represents face of a @see BlockModel.
class BlockFaceModel
{
	std::array<Point, 4> _textureCoordinates;

public:

	/// @brief The constructor.
	/// @param uvTextureCoordinates - UV texture coordinates.
	///	@param texture - The texture that the model is covered with.
	explicit BlockFaceModel(std::array<Point, 4> uvTextureCoordinates);

	std::array<Point, 4>& GetUvCoordinates();
};
