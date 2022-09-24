#pragma once
#include "Core/Log.h"
#include "Core/Metadata.h"

/// @class World
///	@brief Represents the world which contains the data about the generated world
class World
{
	Metadata _worldData;
	Log& _log = Log::Get();

public:

	///	@brief The constructor that takes the pointer to the metadata file.
	///	@remark The metadata doesn't need to be initialized.
	explicit World(const std::string& filename) : _worldData(filename)
	{
	}

	/// @brief Generates the world and creates the file with the world data.
	///	@todo This function is not implemented yet.
	void Create();

	/// @brief Loads the world from the file.
	///	@todo This function is not implemented yet.
	void Load();

	/// @brief Checks if the world is loaded.
	///	@return If the world was correctly loaded from file returns true, otherwise false.
	///	@todo This function is not implemented yet.
	bool IsLoaded();

	/// @brief Saves the world with it's contents.
	///	@todo This function is not implemented yet.
	void Save();
};

