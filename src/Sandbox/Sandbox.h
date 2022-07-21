#pragma once
#include "World.h"
#include "Core/Log.h"
#include "Core/Metadata.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Sandbox
{
	World* world = nullptr;
	Log& log = Log::Get();

public:
	Sandbox() = delete;
	Sandbox(const Sandbox& x) = delete;
	Sandbox(Sandbox&& x) = default;
	Sandbox& operator=(Sandbox x) = delete;
	Sandbox& operator=(Sandbox&& x) = delete;

	explicit Sandbox(const std::string& filename) : world(new World(filename))
	{
		world->Load();
	}

	void Run();

	~Sandbox()
	{
		delete world;
	}
};

