#pragma once
#include <memory>
#include <vector>

#include "Application/Layer/Layer.h"

class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers;
	static void DispatchEvent(Layer& layer, Event& eventToProcess)
	{
		switch(eventToProcess.GetType())
		{
			case EventType::keyboard:   layer.OnEvent(dynamic_cast<KeyboardEvent&>(eventToProcess)); break;
			case EventType::window:		layer.OnEvent(dynamic_cast<WindowEvent&>(eventToProcess));   break;
			case EventType::mouse:		layer.OnEvent(dynamic_cast<MouseEvent&>(eventToProcess));    break;
		}
	}

public:
	void Push(std::unique_ptr<Layer> layer)
	{
		_layers.emplace_back(std::move(layer));
	}

	void Pop()
	{
		_layers.pop_back();
	}

	void Update() const
	{
		for (const auto& layer : _layers)
		{
			layer->OnUpdate();
		}
	}

	void Process(Event& eventToProcess) const
	{
		for (auto i = _layers.size(); i > 0; --i)
		{
			if (eventToProcess.WasHandled()) break;

			DispatchEvent(*_layers[i - 1], eventToProcess);
			glfwPollEvents();
		}
	}
};

