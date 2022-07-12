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

	file.close();
}

void Metadata::Save(const bool overrideFileIfExists) const
{
	if (this->filename.empty())
	{
		throw std::invalid_argument("File is not specified!");
	}

	if (!overrideFileIfExists && this->DoesFileExist(this->filename))
	{
		throw std::runtime_error("An attempt of overriding protected file!");
	}

	std::ofstream file(this->filename);
	rapidjson::OStreamWrapper jsonOutputStream(file);

	rapidjson::Writer<rapidjson::OStreamWrapper> writer(jsonOutputStream);
	this->document.Accept(writer);

	file.close();
}

bool Metadata::GetBool(const std::string& name)
{
	try
	{
		ValidateIfDocumentIsLoaded();
		ValidateIfValueHasGivenType(name, HandledTypes::BOOL);
		return this->document[name.c_str()].GetBool();
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
		this->document[name.c_str()].SetBool(value);
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
		ValidateIfValueHasGivenType(name, HandledTypes::INT);
		return this->document[name.c_str()].GetInt();
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
		this->document[name.c_str()].SetInt(value);
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
		ValidateIfValueHasGivenType(name, HandledTypes::DOUBLE);
		return this->document[name.c_str()].GetDouble();
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
		this->document[name.c_str()].SetDouble(value);
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
		ValidateIfValueHasGivenType(name, HandledTypes::STRING);
		return this->document[name.c_str()].GetString();
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
		this->document[name.c_str()].SetString(rapidjson::StringRef(value.c_str()));
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
		return this->document[name.c_str()].IsNull();
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
		this->document[name.c_str()].SetNull();
	}
	catch(.../*const std::exception& err*/)
	{
		///TODO
		///Remove the dots and uncomment the code
		///Add logging exceptions using Logger
	}
}
