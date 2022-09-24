#include "HumanInterfaceDevice.h"

std::string HumanInterfaceDevice::KeyDescription(const KeyboardKey& key) const
{
	switch(key)
	{
	case KeyboardKey::a: return "A";
	case KeyboardKey::d: return "D";
	case KeyboardKey::s: return "S";
	case KeyboardKey::w: return "W";
	
	case KeyboardKey::escape: return "ESC";
	case KeyboardKey::space: return "SPACE";
	case KeyboardKey::leftShift: return "LEFT SHIFT";
	case KeyboardKey::rightShift: return "RIGHT SHIFT";
	case KeyboardKey::leftCtrl: return "LEFT CTRL";
	case KeyboardKey::rightCtrl: return "RIGHT CTRL";
	}

	_log.Warn("Key code " + std::to_string(static_cast<int>(key)) + " description not found!");
	return std::to_string(static_cast<int>(key));
}

std::string HumanInterfaceDevice::ButtonDescription(const MouseButton& button) const
{
	switch(button)
	{
	case MouseButton::left: return "LEFT BUTTON";
	case MouseButton::right: return "RIGHT BUTTON";
	}

	_log.Warn("Button code " + std::to_string(static_cast<int>(button)) + " description not found!");
	return std::to_string(static_cast<int>(button));
}

int HumanInterfaceDevice::GetState(const KeyboardKey& key) const
{
	return glfwGetKey(_window, static_cast<int>(key));
}

int HumanInterfaceDevice::GetState(const MouseButton& button) const
{
	return glfwGetMouseButton(_window, static_cast<int>(button));
}

void HumanInterfaceDevice::ResetOnceHandledInputStates()
{
	_onceHandledKeyboardKeys.clear();
	_onceHandledMouseButtons.clear();
}

HumanInterfaceDevice::HumanInterfaceDevice(GLFWwindow*& window) : _window(window)
{
}

bool HumanInterfaceDevice::IsPressed(const KeyboardKey& key) const
{
	if (GetState(key) == GLFW_PRESS)
	{
		_log.Trace("Key pressed: " + KeyDescription(key));
		return true;
	}
	
	return false;
}

bool HumanInterfaceDevice::IsPressedOnce(const KeyboardKey& key)
{
	if (GetState(key) == GLFW_PRESS && _onceHandledKeyboardKeys.find(key) == _onceHandledKeyboardKeys.end())
	{
		_onceHandledKeyboardKeys.insert(key);
		return IsPressed(key);
	}

	if (IsReleased(key))
	{
		ResetOnceHandledInputStates();
	}

	return false;
}

bool HumanInterfaceDevice::IsReleased(const KeyboardKey& key) const
{
	return GetState(key) == GLFW_RELEASE;
}

bool HumanInterfaceDevice::IsPressed(const MouseButton& button) const
{
	if (GetState(button) == GLFW_PRESS)
	{
		_log.Trace("Button pressed: " + ButtonDescription(button));
		return true;
	}

	return false;
}

bool HumanInterfaceDevice::IsPressedOnce(const MouseButton& button)
{
	if (GetState(button) == GLFW_PRESS && _onceHandledMouseButtons.find(button) == _onceHandledMouseButtons.end())
	{
		_onceHandledMouseButtons.insert(button);
		return IsPressed(button);
	}

	if (IsReleased(button))
	{
		ResetOnceHandledInputStates();
	}

	return false;
}

bool HumanInterfaceDevice::IsReleased(const MouseButton& button) const
{
	return GetState(button) == GLFW_RELEASE;
}
