// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include "Geometry/Structures.h"
#include "Geometry/Shader.h"
#include "Geometry/VertexArray.h"
#include "Geometry/ElementBuffer.h"
#include "Application/Sandbox/Camera.h"
#include "Application/Sandbox/Model/Surface/Texture.h"

class Mesh
{
protected:
	VertexArray _vao;
public:
	virtual ~Mesh() = default;
};