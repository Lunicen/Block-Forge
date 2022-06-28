#include "Metadata.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/ostreamwrapper.h"
#include <sys/stat.h>
#include <fstream>
#include <sstream>

bool Metadata::DoesFileExist(const std::string& filename)
{
	struct stat buffer{};

	if (stat(filename.c_str(), &buffer) == 0)
	{
		return true;
	}
	return false;
}

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

	std::ifstream file(filename);

	if (!file.good())
	{
		throw std::runtime_error("File doesn't exist!");
	}

	rapidjson::IStreamWrapper jsonInputStream(file);
	this->document.ParseStream(jsonInputStream);
}

void Metadata::Save(const bool overrideFileIfExists) const
{
	if (filename.empty())
	{
		throw std::invalid_argument("File is not specified!");
	}

	if (!overrideFileIfExists && this->DoesFileExist(filename))
	{
		throw std::runtime_error("An attempt of overriding protected file!");
	}

	std::ofstream file(filename);
	rapidjson::OStreamWrapper jsonOutputStream(file);

	rapidjson::Writer<rapidjson::OStreamWrapper> writer(jsonOutputStream);
	this->document.Accept(writer);
}
