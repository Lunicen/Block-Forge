#pragma once

#include <string>
#include <nlohmann/json.hpp>

/// @class Metadata
/// @brief Handles JSON files and manipulates them.
/// @details This class is made for handling the metadata stored in JSON files.
class Metadata
{
	std::string filename;
	nlohmann::json document = nullptr;

	static bool IsFileEmpty(std::ifstream& file);
	static bool DoesFileExist(const std::string& filename);

	void CheckIfFilenameIsNotEmpty() const;
	void ValidateIfDocumentIsLoaded() const;
	void ValidateIfKeyExists(const std::string& name) const;
	static void ValidateIfTypeIsMatched(const nlohmann::json& value, const std::string& requestedType);

	void TryToLoadFile(const std::string& filename);
	void TryToSaveFile() const;

public:
	/// @brief Metadata object constructor.
	Metadata() = default;

	/// @brief Metadata object constructor.
	/// @param filename - Filename of the JSON file.
	explicit Metadata(const std::string& filename);

	/// @brief Set filename.
    /// @param filename - Filename of the JSON file.
	void SetFilename(const std::string& filename);

	/// @brief Get filename.
    /// @retval String with a filename of the JSON file.
	std::string GetFilename();

	/// @brief Loads JSON data to the document variable.
	void Load();

	/// @brief Loads JSON data to the document variable using the given filename.
	/// @param filename - Filename of the JSON file.
	void Load(const std::string& filename);

	bool IsLoaded() const;

	/// @brief Saves JSON data to the file specified in the filename.
	void Save() const;

	/// @brief 
	/// @param name
	nlohmann::json GetObject(const std::string& name);

	/// @brief 
	/// @param name
	/// @param value
	void SetObject(const std::string& name, const nlohmann::json& value);

	/// @brief 
	/// @param name
	bool GetBool(const std::string& name);

	/// @brief 
	/// @param name
	/// @param value
	void SetBool(const std::string& name, bool value);

	/// @brief 
	/// @param name
	int GetInt(const std::string& name);

	/// @brief 
	/// @param name
	/// @param value
	void SetInt(const std::string& name, const int& value);

	/// @brief 
	/// @param name
	double GetDouble(const std::string& name);

	/// @brief 
	/// @param name
	void SetDouble(const std::string& name, const double& value);

	/// @brief 
	/// @param name
	std::string GetString(const std::string& name);

	/// @brief 
	/// @param name
	/// @param value
	void SetString(const std::string& name, const std::string& value);

	/// @brief 
	/// @param name
	bool IsNull(const std::string& name) const;

	/// @brief 
	/// @param name
	void SetNull(const std::string& name);
};

/// @overload void Load()
