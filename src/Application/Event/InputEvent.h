#pragma once
#include "Event.h"
#include "Application/HID/HumanInterfaceDevice.h"

class InputEvent final : public Event
{
	HumanInterfaceDevice& _hid;

public:
	explicit InputEvent(HumanInterfaceDevice& hid) : _hid(hid)
	{
	}

	/// @brief Checks if the requested key is pressed.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed, otherwise false.
	bool IsPressed(const KeyboardKey& key)
	{
		return GetResultAndUpdateFlag(_hid.IsPressed(key));
	}

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed and was not before, otherwise false.
	bool IsPressedOnce(const KeyboardKey& key)
	{
		return GetResultAndUpdateFlag(_hid.IsPressedOnce(key));
	}

	/// @brief Checks if the requested button is pressed.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed, otherwise false.
	bool IsPressed(const MouseButton& button)
	{
		return GetResultAndUpdateFlag(_hid.IsPressed(button));
	}

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed and was not before, otherwise false.
	bool IsPressedOnce(const MouseButton& button)
	{
		return GetResultAndUpdateFlag(_hid.IsPressedOnce(button));
	}

	EventType GetType() override
	{
		return EventType::input;
	}
};
