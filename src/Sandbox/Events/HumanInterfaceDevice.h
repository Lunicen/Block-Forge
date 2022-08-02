#pragma once
#include <GLFW/glfw3.h>
#include "KeyCodes.h"

class HumanInterfaceDevice
{
	GLFWwindow*& _window;

public:
	explicit HumanInterfaceDevice(GLFWwindow*& window);

	bool IsKeyPressed(const KeyboardKey& key) const;
	bool IsKeyReleased(const KeyboardKey& key) const;

	bool IsButtonPressed(const MouseButton& button) const;
	bool IsButtonReleased(const MouseButton& button) const;
};

