#include "HIDEventReporter.h"

#include "Application/EventQueue.h"

int HIDEventReporter::GetState(const KeyboardKey& key) const
{
	return glfwGetKey(_window.GetHandle(), static_cast<int>(key));
}

int HIDEventReporter::GetState(const MouseButton& button) const
{
	return glfwGetMouseButton(_window.GetHandle(), static_cast<int>(button));
}

void HIDEventReporter::ReportKeyboard()
{
	for (auto& key : KeyboardMap)
	{
		const auto& state = GetState(key);

		if (state == GLFW_PRESS)
		{
			if (_onceHandledKeyboardKeys.find(key) == _onceHandledKeyboardKeys.end())
			{
				_onceHandledKeyboardKeys.insert(key);
				EventQueue::Push(std::make_unique<KeyboardEvent>(key, KeyboardAction::isPressedOnce));

				return;
			}
			
			EventQueue::Push(std::make_unique<KeyboardEvent>(key, KeyboardAction::isPressed));
		}

		if (state == GLFW_RELEASE)
		{
			_onceHandledKeyboardKeys.erase(key);
		}
	}
}

void HIDEventReporter::ReportMouse()
{
	for (auto& button : MouseMap)
	{
		const auto& state = GetState(button);

		if (state == GLFW_PRESS)
		{
			if (_onceHandledMouseButtons.find(button) == _onceHandledMouseButtons.end())
			{
				_onceHandledMouseButtons.insert(button);
				EventQueue::Push(std::make_unique<MouseEvent>(button, MouseAction::isPressedOnce));

				return;
			}
			
			EventQueue::Push(std::make_unique<MouseEvent>(button, MouseAction::isPressed));
		}

		if (state == GLFW_RELEASE)
		{
			_onceHandledMouseButtons.erase(button);
		}
	}
}

HIDEventReporter::HIDEventReporter(Window& window) : _window(window)
{
}

void HIDEventReporter::Report()
{
	ReportKeyboard();
	ReportMouse();
}
