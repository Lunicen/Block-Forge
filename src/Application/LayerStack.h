#pragma once
#include <memory>
#include <vector>

#include "Layer/Layer.h"

class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers;
	static void DispatchEvent(Layer& layer, Event& eventToProcess);

	size_t _initialWindowWidth;
	size_t _initialWindowHeight;

public:
	explicit LayerStack(size_t windowWidth, size_t windowHeight);

	void Push(std::unique_ptr<Layer> layer);
	void Pop();

	void Update() const;
	void Process(Event& eventToProcess) const;
};

