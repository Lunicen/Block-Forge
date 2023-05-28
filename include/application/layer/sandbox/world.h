#pragma once
#include "core/log.h"
#include "core/metadata.h"

/// @class World
///	@brief Represents the world which contains the data about the generated world
class World
{
	Metadata _worldData;
	Log& _log = Log::Get();

public:

	///	@brief The constructor that takes the pointer to the metadata file.
	///	@remark The metadata does not need to be initialized.
	explicit World(const std::string& filename) : _worldData(filename)
	{
	}
};

