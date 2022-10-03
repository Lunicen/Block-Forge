#pragma once
#include "BlockFaceModel.h"

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


/// @brief Represents visibility of the faces.
struct FacesVisibility
{
	/// @brief Answers the question "Is the front face of this block visible?".
	bool front;

	/// @brief Answers the question "Is the back face of this block visible?".
	bool back;

	/// @brief Answers the question "Is the left face of this block visible?".
	bool left;

	/// @brief Answers the question "Is the right face of this block visible?".
	bool right;

	/// @brief Answers the question "Is the top face of this block visible?".
	bool top;

	/// @brief Answers the question "Is the bottom face of this block visible?".
	bool bottom;
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
	explicit BlockModel(const BlockFaces& faces)
		: _blockFaces(faces)
	{}

	/// @brief Returns the faces data of the block.
	BlockFaces& GetFaces()
	{
		return _blockFaces;
	}
};