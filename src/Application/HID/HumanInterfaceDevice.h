#pragma once
#include <unordered_set>

#include "Core/Log.h"
#include "KeyCodes.h"
#include "Application/Window.h"


/// @class HumanInterfaceDevice
/// @brief Handles and defines input devices.
///	@details This class handles Human Interface Devices and defines the behaviour of events that support them.
class HumanInterfaceDevice
{
	Log& _log = Log::Get();
	Window& _window;

	std::unordered_set<KeyboardKey> _onceHandledKeyboardKeys;
	std::unordered_set<MouseButton> _onceHandledMouseButtons;

	int GetState(const KeyboardKey& key) const;
	int GetState(const MouseButton& button) const;

public:

	/// @brief The constructor.
	///	@param window - The window in which the simulation is played.
	explicit HumanInterfaceDevice(Window& window);

	/// @brief Checks if the requested key is pressed.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed, otherwise false.
	bool IsPressed(const KeyboardKey& key) const;

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param key - The key from keyboard.
	///	@return Returns true is the key is pressed and was not before, otherwise false.
	bool IsPressedOnce(const KeyboardKey& key);

	/// @brief Checks if the requested button is pressed.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed, otherwise false.
	bool IsPressed(const MouseButton& button) const;

	/// @brief Checks if the requested key is pressed **only** once.
	///	@param button - The button from mouse.
	///	@return Returns true is the button is pressed and was not before, otherwise false.
	bool IsPressedOnce(const MouseButton& button);

	/// @brief Returns the current cursor position.
	std::pair<double, double> GetCursorPosition() const;

	/// @brief Sets the cursor position to the desired location.
	///	@param x - Cursor X location.
	///	@param y - Cursor Y location.
	void SetCursorPosition(double x, double y) const;

	/// @brief Enables cursor making it visible.
	void EnableCursor() const;

	/// @brief Disables cursor making it invisible.
	void DisableCursor() const;
};