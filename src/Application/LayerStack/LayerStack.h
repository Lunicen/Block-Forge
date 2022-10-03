#pragma once
#include <memory>
#include <vector>

#include "Application/Layer/Layer.h"


/// @class LayerStack
///	@brief Represents the stack that can process layers of content that
///	is displayed on the screen.
///	@details This structure handles the priority of what should be interactive on the screen.
class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers{};

public:

	/// @brief Pushes the layer onto the stack.
	void Push(std::unique_ptr<Layer> layer)
	{
		_layers.emplace_back(std::move(layer));
	}

	/// @brief Pops the layer from the stack.
	void Pop()
	{
		_layers.pop_back();
	}

	/// @brief Calls the OnUpdate() methods of the layers.
	void Update() const
	{
		for (const auto& layer : _layers)
		{
			layer->OnUpdate();
		}
	}

	/// @brief Calls the OnEvent() methods of the layers respecting the lock
	/// @param hid - Reference to the Human Interface Device.
	void ProcessEvents(HumanInterfaceDevice& hid) const
	{
		for (auto i = _layers.size(); i > 0; --i)
		{
			auto& layer = _layers[i - 1];

			layer->OnEvent(hid);
			if (layer->IsLocked()) break;
		}
	}
};

