#pragma once
#include <memory>

#include "Mesh/Mesh.h"

/// @class Model
///	@brief Represents a <a href="https://en.wikipedia.org/wiki/Graphical_model" target="_blank">graphical model</a>.
class Model
{
protected:

	/// @brief Mesh of a model.
	std::unique_ptr<Mesh> _mesh;

	/// @brief Texture of a model.
	std::shared_ptr<Texture> _texture;
};
