#pragma once
#include <unordered_set>

#include "Application/Window.h"
#include "HIDMap.h"

class HIDEventReporter
{
	Window& _window;

	std::unordered_set<KeyboardKey> _onceHandledKeyboardKeys;
	std::unordered_set<MouseButton> _onceHandledMouseButtons;

	int GetState(const KeyboardKey& key) const;
	int GetState(const MouseButton& button) const;

	void ReportKeyboard();
	void ReportMouse();

public:

	explicit HIDEventReporter(Window& window);
	
	void Report();
};

