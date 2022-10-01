// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include "Geometry/Structures.h"
#include "Geometry/Shader.h"
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Application/Sandbox/Camera.h"
#include "Application/Sandbox/Model/Surface/Texture.h"

/// @class Mesh
///	@brief The interface for the classes which purpose is to create mesh for the models.
class Mesh  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:
	/// @brief Vertex array object of the meshes.
	VertexArray _vao;
public:
	virtual ~Mesh() = default;
};