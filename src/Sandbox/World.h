#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"

class World
{
	std::unique_ptr<Metadata> worldData = nullptr;
	Log& log = Log::Get();

public:
	explicit World(const std::string& filename) : worldData(std::make_unique<Metadata>(filename))
	{
	}

	void Create();
	void Load();
	bool IsLoaded();
	void Save();
};

