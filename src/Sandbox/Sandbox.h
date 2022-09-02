#pragma once
#include "World.h"
#include "Core/Log.h"

/// @class Sandbox
/// @brief Class where the world is projected.
///	@details This class handles displaying the world or so to say the actual simulation.
class Sandbox
{
	World _world;
	Log& _log = Log::Get();

	static void InitializeGlfw();

public:

	/// @brief The constructor, loads the world data.
	///	@param filename - The filename of the file containing the world data.
	explicit Sandbox(const std::string& filename) : _world(World(filename))
	{
		_world.Load();
	}

	/// @brief Initializes the simulation.
	void Run();
};

