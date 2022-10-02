#pragma once
#include "Event.h"

class WindowEvent final : public Event
{
	Window& _window;

public:
	explicit WindowEvent(Window& window) : _window(window)
	{
	}

	EventType GetType() override
	{
		return EventType::window;
	}

	std::pair<size_t, size_t> GetWindowSize()
	{
		MarkEventAsHandled();
		return std::pair<size_t, size_t>(_window.GetWidth(), _window.GetHeight());
	}
};
