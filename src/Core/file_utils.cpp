#include "core/file_utils.h"

#include <fstream>

bool FileUtils::IsFileEmpty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

bool FileUtils::DoesFileExist(const std::string& filename)
{
	struct stat buffer{};

	if (stat(filename.c_str(), &buffer) == 0)
	{
		return true;
	}
	return false;
}
