#pragma once
#include "Application/Window.h"
#include "Event.h"

class WindowEvent final : public Event
{
	Window& _window;

public:
	explicit WindowEvent(Window& window) : _window(window)
	{
	}

	std::pair<size_t, size_t> GetWindowSize()
	{
		MarkEventAsHandled();
		return {_window.GetWidth(), _window.GetHeight()};
	}

	EventType GetType() override
	{
		return EventType::window;
	}
};
