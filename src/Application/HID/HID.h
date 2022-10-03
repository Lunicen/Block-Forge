#pragma once
#include "Core/Log.h"
#include "Application/Window.h"

/// @class HID
/// @brief Handles and defines input devices.
///	@details This class handles Human Interface Devices and defines the behaviour of events that support them.
class HID
{
	Log& _log = Log::Get();
	Window& _window;

public:

	/// @brief The constructor.
	///	@param window - The window in which the simulation is played.
	explicit HID(Window& window);

	std::pair<double, double> GetCursorPosition() const;

	void SetCursorPosition(double x, double y) const;

	void EnableCursor() const;

	void DisableCursor() const;
	
};