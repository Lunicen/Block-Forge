#pragma once
#include <memory>
#include <queue>

#include "Event.h"

class EventQueue
{
	static std::queue<std::unique_ptr<Event>> _eventQueue;

public:
	static void Push(std::unique_ptr<Event> eventToPush)
	{
		_eventQueue.emplace(std::move(eventToPush));
	}

	static std::unique_ptr<Event> Pop()
	{
		auto result = std::move(_eventQueue.front());
		_eventQueue.pop();

		return std::move(result);
	}
};
