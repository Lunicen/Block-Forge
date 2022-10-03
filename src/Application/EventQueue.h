#pragma once
#include <array>

#include "Event/Event.h"
#include "LayerStack/LayerStack.h"


constexpr size_t MaxEventQueueCapacity = 256;

class EventQueue
{
	static std::array<Event*, MaxEventQueueCapacity> _eventQueue;
	static size_t _queueIterator;

public:
	static void Push(Event* eventToPush)
	{
		if (_queueIterator < MaxEventQueueCapacity - 1)
		{
			_eventQueue[_queueIterator++] = eventToPush;
		}
	}

	static void Update(const LayerStack& stack)
	{
		if (_queueIterator > 0)
		{
			--_queueIterator;

			stack.Process(*_eventQueue[_queueIterator]);
			delete _eventQueue[_queueIterator];
		}
	}
};
