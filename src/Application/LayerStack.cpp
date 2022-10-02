#include "LayerStack.h"

void LayerStack::DispatchEvent(Layer& layer, Event& eventToProcess)
{
	switch(eventToProcess.GetType())
	{
		case EventType::input:  layer.OnEvent(dynamic_cast<InputEvent&>(eventToProcess));  break;
		case EventType::window: layer.OnEvent(dynamic_cast<WindowEvent&>(eventToProcess)); break;
	}
}

void LayerStack::Push(std::unique_ptr<Layer> layer)
{
	layer->Initialize();
	_layers.emplace_back(std::move(layer));
}

void LayerStack::Pop()
{
	_layers.front()->Destroy();
	_layers.pop_back();
}

void LayerStack::Update() const
{
	for (const auto& layer : _layers)
	{
		layer->OnUpdate();
	}
}

void LayerStack::Process(Event& eventToProcess) const
{
	for (auto i = _layers.size(); i > 0; --i)
	{
		if (eventToProcess.WasHandled()) break;

		DispatchEvent(*_layers[i - 1], eventToProcess);
	}
}
