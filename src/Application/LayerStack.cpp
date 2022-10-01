#include "LayerStack.h"

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
		_layers[i - 1]->OnEvent(eventToProcess);
	}
}
