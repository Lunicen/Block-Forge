#pragma once
#include "Core/OpenGLHeaders.h"

enum class KeyboardKey
{
	w = GLFW_KEY_W,
	a = GLFW_KEY_A,
	s = GLFW_KEY_S,
	d = GLFW_KEY_D,

	escape	= GLFW_KEY_ESCAPE,
	space	= GLFW_KEY_SPACE,

	leftShift	= GLFW_KEY_LEFT_SHIFT,
	rightShift	= GLFW_KEY_RIGHT_SHIFT,
	leftCtrl	= GLFW_KEY_LEFT_CONTROL,
	rightCtrl	= GLFW_KEY_RIGHT_CONTROL
};

enum class MouseButton
{
	left = GLFW_MOUSE_BUTTON_LEFT,
	right = GLFW_MOUSE_BUTTON_RIGHT
};