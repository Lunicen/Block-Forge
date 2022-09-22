#pragma once
#include "Model.h"

/// @class BlockFaceModel
///	@brief Represents face of a @see BlockModel.
class BlockFaceModel : public Model
{
public:

	/// @brief The constructor.
	/// @param mesh - The mesh of the model.
	///	@param texture - The texture that the model is covered with.
	BlockFaceModel(std::unique_ptr<Mesh>& mesh, std::shared_ptr<Texture> texture);

	/// @brief Draws the face of a block.
	/// @param origin - A position in the world to place the model.
	///	@param camera - It is used to bind a shader to see the drawn model.
	void Draw(const Position& origin, const Camera& camera) const;
};
