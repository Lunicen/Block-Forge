#pragma once
#include "Layer/Layer.h"

class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers;

public:
	void Push(std::unique_ptr<Layer> layer);
	void Pop();

	void Update() const;
	void Process(Event& eventToProcess) const;
};

