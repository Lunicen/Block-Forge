#pragma once
#include <unordered_set>
#include "Core/Log.h"
#include <GLFW/glfw3.h>
#include "KeyCodes.h"


class HumanInterfaceDevice
{
	Log& _log = Log::Get();
	GLFWwindow*& _window;
	std::unordered_set<KeyboardKey> _onceHandledKeyboardKeys;
	std::unordered_set<MouseButton> _onceHandledMouseButtons;

	std::string KeyDescription(const KeyboardKey& key) const;
	std::string ButtonDescription(const MouseButton& button) const;

	int GetState(const KeyboardKey& key) const;
	int GetState(const MouseButton& button) const;
	void ResetOnceHandledInputStates();

public:
	explicit HumanInterfaceDevice(GLFWwindow*& window);

	bool IsPressed(const KeyboardKey& key) const;
	bool IsPressedOnce(const KeyboardKey& key);
	bool IsReleased(const KeyboardKey& key) const;

	bool IsPressed(const MouseButton& button) const;
	bool IsPressedOnce(const MouseButton& button);
	bool IsReleased(const MouseButton& button) const;
};

