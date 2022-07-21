#pragma once
#include "Core/Metadata.h"

class World
{
	Metadata* worldData;

public:
	World() = delete;

	explicit World(const std::string& filename) : worldData(new Metadata(filename))
	{
	}

	void Create();
	void Load();
	void Save();
};

