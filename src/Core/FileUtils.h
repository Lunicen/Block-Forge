#pragma once
#include <string>

class FileUtils
{
protected:
	static bool IsFileEmpty(std::ifstream& file);
	static bool DoesFileExist(const std::string& filename);
};

