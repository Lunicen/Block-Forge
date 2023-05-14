#pragma once
#include "Core/OpenGLHeaders.h"

enum class KeyboardKey
{
	w = GLFW_KEY_W,
	a = GLFW_KEY_A,
	s = GLFW_KEY_S,
	d = GLFW_KEY_D,

	key1 = GLFW_KEY_1,
	key2 = GLFW_KEY_2,
	key3 = GLFW_KEY_3,
	key4 = GLFW_KEY_4,
	key5 = GLFW_KEY_5,
	key6 = GLFW_KEY_6,
	key7 = GLFW_KEY_7,
	key8 = GLFW_KEY_8,
	key9 = GLFW_KEY_9,
	key0 = GLFW_KEY_0,

	plus = GLFW_KEY_EQUAL,
	minus = GLFW_KEY_MINUS,
	
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
	right = GLFW_MOUSE_BUTTON_RIGHT,
};