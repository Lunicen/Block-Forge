#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"

class World
{
	Metadata* worldData = nullptr;
	Log& log = Log::Get();

public:
	World() = delete;
	World(const World&) = default;
	World(World&&) = delete;
	World& operator=(World) = delete;
	World& operator=(World&&) = delete;

	explicit World(const std::string& filename) : worldData(new Metadata(filename))
	{
	}

	void Create();
	void Load();
	bool IsLoaded();
	void Save();

	~World()
	{
		delete worldData;
	}
};

