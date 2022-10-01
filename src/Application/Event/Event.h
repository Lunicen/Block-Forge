#pragma once
#include "HumanInterfaceDevice.h"
#include "KeyCodes.h"

class Event
{
	bool _wasHandled = false;
	HumanInterfaceDevice& _hid;

	bool GetFunctionalityResultAndUpdateFlag(bool resultWasSuccessful);

public:
	explicit Event(HumanInterfaceDevice& hid);

	bool IsActive() const;

	/// @brief Checks if the requested key is pressed.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed, otherwise false.
	bool IsPressed(const KeyboardKey& key);

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed and was not before, otherwise false.
	bool IsPressedOnce(const KeyboardKey& key);



	/// @brief Checks if the requested button is pressed.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed, otherwise false.
	bool IsPressed(const MouseButton& button);

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed and was not before, otherwise false.
	bool IsPressedOnce(const MouseButton& button);
};
