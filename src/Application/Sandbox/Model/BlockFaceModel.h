#pragma once
#include "Mesh/Mesh.h"

/// @class BlockFaceModel
///	@brief Represents face of a @see BlockModel.
class BlockFaceModel
{
	std::array<Point, VerticesInQuad> _textureCoordinates{};

public:

	/// @brief The constructor.
	/// @param uvTextureCoordinates - UV texture coordinates.
	explicit BlockFaceModel(const std::array<Point, VerticesInQuad>& uvTextureCoordinates);

	/// @brief Returns the uv coordinates associated with the face model.
	std::array<Point, VerticesInQuad>& GetUvCoordinates();
};
