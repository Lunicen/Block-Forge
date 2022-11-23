#pragma once
#include <array>
#include "Mesh/Geometry/Structures.h"

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


/// @brief Container for the face models of a block.
struct BlockFaces
{
	/// @brief Model of the block front face.
	BlockFaceModel front;

	/// @brief Model of the block back face.
	BlockFaceModel back;

	/// @brief Model of the block left face.
	BlockFaceModel left;

	/// @brief Model of the block right face.
	BlockFaceModel right;

	/// @brief Model of the block top face.
	BlockFaceModel top;

	/// @brief Model of the block bottom face.
	BlockFaceModel bottom;
};

/// @class BlockModel
///	@brief Represents a <a href="https://en.wikipedia.org/wiki/Graphical_model" target="_blank">graphical model</a> of a block.
///	@note This class is not an actual model.
///	More like container for the @see BlockFaceModel objects. But it suits well it's definition and
///	has functionality that makes sense.
class BlockModel
{
	BlockFaces _blockFaces;

public:

	/// @brief The constructor.
	///	@param faces - The faces of the block.
	explicit BlockModel(const BlockFaces& faces) : _blockFaces(faces) {}

	/// @brief Returns the faces data of the block.
	BlockFaces& GetFaces() {
		return _blockFaces;
	}
};