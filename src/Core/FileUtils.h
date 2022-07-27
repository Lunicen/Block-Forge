#pragma once
#include <string>

/// @class FileUtils
/// @brief This is a file utilities class that contains functions that
/// could be mostly used by classes that are using I/O file operations.
class FileUtils
{
protected:
	/// @brief Checks if file is empty.
	///	@param file - input filestream of the file.
	///	@return true if file is empty, otherwise false.
	static bool IsFileEmpty(std::ifstream& file);

	/// @brief Checks if file exists.
	///	@param filename - Filename of the file.
	///	@return true if file exists, otherwise false.
	static bool DoesFileExist(const std::string& filename);
};

