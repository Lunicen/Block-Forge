#pragma once
#include <memory>
#include <queue>

#include "Event/Event.h"
#include "LayerStack/Stack/SandboxStack.h"


class EventQueue
{
	static std::queue<std::unique_ptr<Event>> _eventQueue;

public:
	static void Push(std::unique_ptr<Event> eventToPush)
	{
		_eventQueue.emplace(std::move(eventToPush));
	}

	static void Update(const LayerStack& stack)
	{
		if (!_eventQueue.empty())
		{
			const auto result = std::move(_eventQueue.front());
			_eventQueue.pop();

			stack.Process(*result);
		}
	}
};

std::queue<std::unique_ptr<Event>> EventQueue::_eventQueue;
