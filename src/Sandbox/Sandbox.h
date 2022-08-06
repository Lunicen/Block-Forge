#pragma once
#include "World.h"
#include "Core/Log.h"

/// @class Sandbox
/// @brief Class where the world is projected.
///	@details This class handles displaying the world or so to say the actual simulation.
class Sandbox
{
	std::unique_ptr<World> _world = nullptr;
	Log& _log = Log::Get();
private:
	static void InitializeGlfw(); //TODO uwaga ta funkcja jest te¿ w main menu, mo¿e przenieœæ gdzieœ indziej j¹ w takim wypadku?


public:

	/// @brief The constructor, loads the world data.
	///	@param filename - The filename of the file containing the world data.
	explicit Sandbox(const std::string& filename) : _world(std::make_unique<World>(filename))
	{
		_world->Load();
	}

	/// @brief Initializes the simulation.
	void Run() const;
};

