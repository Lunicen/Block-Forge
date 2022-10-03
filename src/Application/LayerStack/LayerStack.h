#pragma once
#include <memory>
#include <vector>

#include "Application/Layer/Layer.h"

class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers{};

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

	void ProcessEvents() const
	{
		for (auto i = _layers.size(); i > 0; --i)
		{
			auto& layer = _layers[i - 1];

			layer->OnEvent();
			if (layer->IsLocked()) break;
		}
	}
};

