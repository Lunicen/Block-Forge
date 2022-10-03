#pragma once
class EventListener
{
	bool _eventOccurred = false;

public:
	void RegisterEvent()
	{
		_eventOccurred = true;
	}

	void Reset()
	{
		_eventOccurred = false;
	}

	bool HasEventOccurred() const
	{
		return _eventOccurred;
	}
};