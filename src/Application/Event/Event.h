#pragma once
enum class EventType
{
	input = 0,
	window
};

class Event  // NOLINT(cppcoreguidelines-special-member-functions)
{
	bool _wasHandled = false;

public:
	bool WasHandled() const
	{
		return _wasHandled;
	}

	bool GetResultAndUpdateFlag(const bool resultWasSuccessful)
	{
		if (resultWasSuccessful)
		{
			_wasHandled = true;
			return true;
		}

		return false;
	}

	void MarkEventAsHandled()
	{
		_wasHandled = true;
	}

	virtual EventType GetType() = 0;

	virtual ~Event() = default;
};
