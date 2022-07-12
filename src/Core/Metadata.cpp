#include "Metadata.h"
#include <sys/stat.h>
#include <fstream>
#include <nlohmann/json.hpp>

bool Metadata::IsFileEmpty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

bool Metadata::DoesFileExist(const std::string& filename)
{
	struct stat buffer{};

	if (stat(filename.c_str(), &buffer) == 0)
	{
		return true;
	}
	return false;
}

void Metadata::CheckIfFilenameIsNotEmpty() const
{
	if (this->filename.empty())
		throw std::runtime_error("File is not specified!");
}

void Metadata::ValidateIfDocumentIsLoaded() const
{
	if (this->document == nullptr)
		throw std::runtime_error("The data is not loaded!");
}

void Metadata::ValidateIfKeyExists(const std::string& name) const
{
	if (!this->document.contains(name))
		throw std::runtime_error("The key " + name + "doesn't exist!");
}

void Metadata::ValidateIfTypeIsMatched(const nlohmann::json& value, const std::string& requestedType)
{
	const std::string valueType = value.type_name();

	if (valueType != requestedType)
		throw std::runtime_error("The value type is " + valueType + "! Requested " + requestedType);
}

void Metadata::TryToLoadFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.good())
	{
		throw std::runtime_error("File doesn't exist!");
	}

	if (IsFileEmpty(file))
	{
		this->document = nlohmann::json::parse("{}");
	}
	else
	{
		this->document = nlohmann::json::parse(file);
	}
	
	file.close();
}

void Metadata::TryToSaveFile() const
{
	std::ofstream file(this->filename);
	file << this->document;
	file.close();
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
	SetFilename(filename);

	try
	{
		CheckIfFilenameIsNotEmpty();
		TryToLoadFile(filename);
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

void Metadata::Save() const
{
	try
	{
		CheckIfFilenameIsNotEmpty();
		TryToSaveFile();
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

nlohmann::json Metadata::GetObject(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);
		ValidateIfTypeIsMatched(this->document[name], "object");

		return this->document[name];
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return false;
}

void Metadata::SetObject(const std::string& name, const nlohmann::json& value)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = value;
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

bool Metadata::GetBool(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);
		ValidateIfTypeIsMatched(this->document[name], "boolean");

		return this->document.value(name, false);
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return false;
}

void Metadata::SetBool(const std::string& name, const bool value)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = value;
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

int Metadata::GetInt(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);
		ValidateIfTypeIsMatched(this->document[name], "number");
		
		return this->document.value(name, 0);
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return 0;
}

void Metadata::SetInt(const std::string& name, const int& value)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = value;
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

double Metadata::GetDouble(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);
		ValidateIfTypeIsMatched(this->document[name], "number");
		
		return this->document.value(name, 0.0);
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return 0.0;
}

void Metadata::SetDouble(const std::string& name, const double& value)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = value;
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

std::string Metadata::GetString(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);
		ValidateIfTypeIsMatched(this->document[name], "number");
		
		return this->document.value(name, "undefined");
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return "undefined";
}

void Metadata::SetString(const std::string& name, const std::string& value)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = value;
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}

bool Metadata::IsNull(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfKeyExists(name);

		return this->document[name].is_null();
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}

	return false;
}

void Metadata::SetNull(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		this->document[name] = "null";
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}
