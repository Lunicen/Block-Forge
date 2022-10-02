#pragma once
#include "Event.h"

class WindowEvent final : public Event
{
public:
	EventType GetType() override
	{
		return EventType::window;
	}
};
