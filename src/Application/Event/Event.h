#pragma once
enum class EventType
{
	keyboard = 0,
	mouse,
	window
};

class Event
{
	bool _wasHandled = false;

public:

	bool WasHandled() const
	{
		return _wasHandled;
	}

	void MarkEventAsHandled()
	{
		_wasHandled = true;
	}

	virtual EventType GetType() = 0;

	virtual ~Event() = default;
};
