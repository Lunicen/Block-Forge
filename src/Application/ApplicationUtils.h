#pragma once
#include "Core/OpenGLHeaders.h"

struct Window
{
	GLFWwindow* handle;
	size_t width;
	size_t height;
};