#pragma once
#include "Core/Log.h"
#include <GLFW/glfw3.h>
#include "KeyCodes.h"


class HumanInterfaceDevice
{
	Log& _log = Log::Get();

	GLFWwindow*& _window;

	std::string KeyDescription(const KeyboardKey& key) const;
	std::string ButtonDescription(const MouseButton& button) const;

public:
	explicit HumanInterfaceDevice(GLFWwindow*& window);

	bool IsKeyPressed(const KeyboardKey& key) const;
	bool IsKeyReleased(const KeyboardKey& key) const;

	bool IsButtonPressed(const MouseButton& button) const;
	bool IsButtonReleased(const MouseButton& button) const;
};

