#include <fstream>

#include "core/engine_exceptions.h"
#include "core/metadata.h"

void Metadata::CheckIfFilenameIsNotEmpty() const
{
	if (_filename.empty())
	{
		throw UninitializedPropertyAccessException("File is not specified!");
	}
}

void Metadata::ValidateIfDocumentIsLoaded() const
{
	if (_document == nullptr)
	{
		throw UninitializedPropertyAccessException("The data is not loaded!");
	}
}

void Metadata::ValidateIfKeyExists(const std::string& name) const
{
	if (!_document.contains(name))
	{
		throw NotFoundException("The key " + name + "doesn't exist!");
	}
}

void Metadata::ValidateIfTypeIsMatched(const nlohmann::json& value, const std::string& requestedType)
{
	if (const std::string valueType = value.type_name(); valueType != requestedType)
	{
		throw MismatchException("The value type is " + valueType + "! Requested " + requestedType);
	}
}

void Metadata::TryToLoadFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.good())
	{
		throw NotFoundException("File " + filename + " doesn't exist!");
	}

	if (IsFileEmpty(file))
	{
		_document = nlohmann::json::parse("{}");
	}
	else
	{
		_document = nlohmann::json::parse(file);
	}
	
	file.close();
}

void Metadata::TryToSaveFile() const
{
	std::ofstream file(_filename);
	file << _document;
	file.close();
}

Metadata::Metadata(const std::string& filename)
{
	this->SetFilename(filename);
}

void Metadata::SetFilename(const std::string& filename)
{
	_filename = filename;
}

std::string Metadata::GetFilename()
{
	return _filename;
}

void Metadata::Create() const
{
	const auto filename = _filename;

	if (DoesFileExist(filename))
	{
		_log.Warn("Attempting to overwrite file at " + filename);
	}

	std::ofstream file(filename);
	file << "{}";
	file.close();
}

void Metadata::Create(const std::string& filename)
{
	SetFilename(filename);
	Create();
}

void Metadata::Load()
{
	Load(_filename);
}

void Metadata::Load(const std::string& filename)
{
	SetFilename(filename);
	CheckIfFilenameIsNotEmpty();
	TryToLoadFile(filename);
}

void Metadata::Save() const
{
	CheckIfFilenameIsNotEmpty();
	TryToSaveFile();
}

nlohmann::json Metadata::GetJsonObject(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "object");

	return _document[name];
}

void Metadata::SetJsonObject(const std::string& name, const nlohmann::json& value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

nlohmann::json Metadata::GetJsonArray(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "array");

	return _document[name];
}

void Metadata::SetJsonArray(const std::string& name, const nlohmann::json& value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

bool Metadata::GetBool(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "boolean");

	return _document.value(name, false);
}

void Metadata::SetBool(const std::string& name, const bool value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

int Metadata::GetInt(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "number");
		
	return _document.value(name, 0);
}

void Metadata::SetInt(const std::string& name, const int& value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

double Metadata::GetDouble(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "number");
		
	return _document.value(name, 0.0);
}

void Metadata::SetDouble(const std::string& name, const double& value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

std::string Metadata::GetString(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);
	ValidateIfTypeIsMatched(_document[name], "string");

	return _document.value(name, "undefined");
}

void Metadata::SetString(const std::string& name, const std::string& value)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = value;
}

bool Metadata::IsNull(const std::string& name) const
{
	ValidateIfDocumentIsLoaded();
	ValidateIfKeyExists(name);

	if (_document.value(name, "undefined") == "null" || _document[name].is_null())
	{
		return true;
	}
	return false;
}

void Metadata::SetNull(const std::string& name)
{
	ValidateIfDocumentIsLoaded();
	_document[name] = "null";
}
