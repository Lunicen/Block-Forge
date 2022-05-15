#include "Metadata.h"
#include <fstream>
#include <sstream>

Metadata::Metadata(const std::string& filename)
{
	this->SetFilename(filename);
}

void Metadata::SetFilename(const std::string& filename)
{
	this->filename = filename;
}

std::string Metadata::GetFilename()
{
	return this->filename;
}

void Metadata::Load()
{
	Load(this->GetFilename());
}

void Metadata::Load(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument("File is not specified!");
	}

	const std::ifstream file(filename);

	if (!file.good())
	{
		throw std::runtime_error("File doesn't exist!");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	this->document.Parse(buffer.str().c_str());
}
