#include "LayerStack.h"

void LayerStack::DispatchEvent(Layer& layer, Event& eventToProcess)
{
	switch(eventToProcess.GetType())
	{
		case EventType::input:  layer.OnEvent(dynamic_cast<InputEvent&>(eventToProcess));  break;
		case EventType::window: layer.OnEvent(dynamic_cast<WindowEvent&>(eventToProcess)); break;
	}
}

LayerStack::LayerStack(const size_t screenWidth, const size_t screenHeight)
	: _initialScreenWidth(screenWidth), _initialScreenHeight(screenHeight)
{
}

void LayerStack::Push(std::unique_ptr<Layer> layer)
{
	layer->OnInitialize(_initialScreenWidth, _initialScreenHeight);
	_layers.emplace_back(std::move(layer));
}

void LayerStack::Pop()
{
	_layers.front()->OnDestroy();
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
