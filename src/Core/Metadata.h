#pragma once
#include <string>
#include <stdexcept>
#include "rapidjson/document.h"

class Metadata
{
	std::string filename;
	rapidjson::Document document;

public:
	Metadata() = default;
	explicit Metadata(const std::string& filename);

	void SetFilename(const std::string& filename);
	std::string GetFilename();

	void Load();
	void Load(std::string filename);
};

