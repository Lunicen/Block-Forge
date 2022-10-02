#pragma once
#include <memory>
#include <vector>

#include "Layer/Layer.h"

class LayerStack
{
	std::vector<std::unique_ptr<Layer>> _layers;
	static void DispatchEvent(Layer& layer, Event& eventToProcess);

	size_t _initialScreenWidth;
	size_t _initialScreenHeight;

public:
	explicit LayerStack(size_t screenWidth, size_t screenHeight);

	void Push(std::unique_ptr<Layer> layer);
	void Pop();

	void Update() const;
	void Process(Event& eventToProcess) const;
};

