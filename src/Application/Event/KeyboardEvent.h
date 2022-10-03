#pragma once
#include "Event.h"
// ReSharper disable once CppUnusedIncludeDirective
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

enum class KeyboardAction
{
	isPressed = GLFW_PRESS,
	isStillPressed = GLFW_REPEAT
};

class KeyboardEvent final : public Event
{
	KeyboardKey _keyCode;
	KeyboardAction _action;

public:
	explicit KeyboardEvent(const KeyboardKey key, const KeyboardAction action) : _keyCode(key), _action(action)
	{
	}

	/// @brief Checks if the requested key is pressed.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed, otherwise false.
	bool IsPressed(const KeyboardKey& key)
	{
		if (key == _keyCode && (_action == KeyboardAction::isPressed || _action == KeyboardAction::isStillPressed))
		{
			MarkEventAsHandled();
			return true;
		}
		
		return false;
	}

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed and was not before, otherwise false.
	bool IsPressedOnce(const KeyboardKey& key)
	{
		if (key == _keyCode && _action == KeyboardAction::isPressed)
		{
			MarkEventAsHandled();
			return true;
		}
		
		return false;
	}

	EventType GetType() override
	{
		return EventType::keyboard;
	}
};
