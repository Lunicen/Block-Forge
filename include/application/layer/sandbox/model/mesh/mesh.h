// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include "geometry/structures.h"
#include "geometry/shader.h"
#include "geometry/vertex_array.h"
#include "geometry/element_buffer.h"
#include "application/layer/sandbox/camera.h"
#include "application/layer/sandbox/model/surface/texture.h"

/// @class Mesh
///	@brief The interface for the classes which purpose is to create mesh for the models.
class Mesh  // NOLINT(cppcoreguidelines-special-member-functions)
{
	/// @brief Vertex array object of the meshes.
	VertexArray _vao;

public:

	/// @brief Returns mesh Vertex Array Object.
	VertexArray& GetVao()
	{
		return _vao;
	}

	virtual ~Mesh() = default;
};