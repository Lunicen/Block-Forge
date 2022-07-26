#pragma once
#include "World.h"
#include "Core/Log.h"

class Sandbox
{
	std::unique_ptr<World> world = nullptr;
	Log& log = Log::Get();

public:
	explicit Sandbox(const std::string& filename) : world(std::make_unique<World>(filename))
	{
		world->Load();
	}

	void Run() const;
};

