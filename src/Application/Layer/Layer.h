#pragma once

class Layer
{
	EventListener& _eventListener;
	bool _isLocked = false;

protected:
	void LockLayer()
	{
		_isLocked = true;
	}

	void UnlockLayer()
	{
		_isLocked = false;
	}

public:

	explicit Layer(EventListener& eventListener) : _eventListener(eventListener)
	{}

	Layer(const Layer&) = default;
	Layer(Layer&&) = default;
	Layer& operator=(const Layer&) = delete;
	Layer& operator=(Layer&&) = delete;

	virtual void OnUpdate() = 0;

	virtual void OnEvent() {}

	bool IsLocked() const
	{
		return _eventListener.HasEventOccurred() || _isLocked;
	}

	virtual ~Layer() = default;
};

