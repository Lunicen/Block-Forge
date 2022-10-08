#pragma once

/// @class Layer
///	@brief Represents a layer that is used by the layer stack.
///	@see LayerStack
class Layer
{
	bool _isLocked = false;

protected:

	/// @brief Locks the layer, so the next ones won't be processed
	///	by the OnEvent() method.
	void LockLayer()
	{
		_isLocked = true;
	}

	/// @brief Unlocks the layer.
	void UnlockLayer()
	{
		_isLocked = false;
	}

public:
	Layer() = default;

	/// @brief Copy constructor.
	Layer(const Layer&) = default;

	/// @brief Move constructor.
	Layer(Layer&&) = default;
	Layer& operator=(const Layer&) = delete;
	Layer& operator=(Layer&&) = delete;

	/// @brief This method is responsible for drawing data on the screen.
	/// @details This method is used basically for rendering.
	///	Add the functionality that handles drawing every frame.
	virtual void OnUpdate() = 0;

	/// @brief This method is used to handle events.
	///	@details This method should be used when you want to declare functionality that is strongly related to this layer.
	///	For example, when you are playing a simulation and you pause the game.
	///	Then you may want to freeze input events that are related to this layer,
	///	but you would like to render the content of this layer.
	///
	///	Using this method, you can tell it to freeze when necessary and
	///	use the OnUpdate() method to render continuously.
	/// @param hid - Reference to the Human Interface Device.
	virtual void OnEvent(HumanInterfaceDevice& hid) = 0;

	/// @brief Checks if this layer is locked.
	///	@details If the layer is locked,
	///	it means that the lower layers from the layer stack should be skipped.
	bool IsLocked() const
	{
		return _isLocked;
	}

	virtual ~Layer() = default;
};

