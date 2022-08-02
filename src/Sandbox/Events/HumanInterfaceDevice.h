#pragma once
#include <GLFW/glfw3.h>

class HumanInterfaceDevice
{
	enum class KeyboardKey
	{
		w = GLFW_KEY_W,
		a = GLFW_KEY_A,
		s = GLFW_KEY_S,
		d = GLFW_KEY_D
	};
	enum class MouseButton
	{
		left = GLFW_MOUSE_BUTTON_LEFT,
		right = GLFW_MOUSE_BUTTON_RIGHT
	};
	GLFWwindow*& _window;

public:
	explicit HumanInterfaceDevice(GLFWwindow*& window);

	bool IsKeyPressed(const KeyboardKey& key) const;
	bool IsKeyReleased(const KeyboardKey& key) const;

	bool IsButtonPressed(const MouseButton& button) const;
	bool IsButtonReleased(const MouseButton& button) const;
};

