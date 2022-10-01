#include "Event.h"

bool Event::GetFunctionalityResultAndUpdateFlag(const bool resultWasSuccessful)
{
	if (resultWasSuccessful)
	{
		_wasHandled = true;
		return true;
	}

	return false;
}

Event::Event(HumanInterfaceDevice& hid) : _hid(hid)
{
}

bool Event::IsActive() const
{
	return !_wasHandled;
}

bool Event::IsPressed(const KeyboardKey& key)
{
	if (_wasHandled) return false;
	return GetFunctionalityResultAndUpdateFlag(_hid.IsPressed(key));
}

bool Event::IsPressedOnce(const KeyboardKey& key)
{
	if (_wasHandled) return false;
	return GetFunctionalityResultAndUpdateFlag(_hid.IsPressedOnce(key));
}

bool Event::IsPressed(const MouseButton& button)
{
	if (_wasHandled) return false;
	return GetFunctionalityResultAndUpdateFlag(_hid.IsPressed(button));
}

bool Event::IsPressedOnce(const MouseButton& button)
{
	if (_wasHandled) return false;
	return GetFunctionalityResultAndUpdateFlag(_hid.IsPressedOnce(button));
}

