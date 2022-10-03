#pragma once
#include "Event.h"
#include "Core/OpenGLHeaders.h"

enum class MouseButton
{
	left = GLFW_MOUSE_BUTTON_LEFT,
	right = GLFW_MOUSE_BUTTON_RIGHT,

	unknown
};

enum class MouseAction
{
	isPressedOnce,
	isPressed = GLFW_PRESS,
	moved
};

class MouseEvent final : public Event
{
	MouseButton _buttonCode;
	MouseAction _action;

public:
	explicit MouseEvent(const MouseButton button, const MouseAction action)
		: _buttonCode(button), _action(action)
	{
	}

	/// @brief Checks if the requested button is pressed.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed, otherwise false.
	bool IsPressed(const MouseButton& button)
	{
		if (_buttonCode == button && _action == MouseAction::isPressed)
		{
			MarkEventAsHandled();
			return true;
		}

		return false;
	}

	EventType GetType() override
	{
		return EventType::mouse;
	}
};