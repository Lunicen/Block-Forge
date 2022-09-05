#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "FileUtils.h"
#include "Log.h"

/// @class Metadata
/// @brief Handles JSON files and manipulates them.
/// @details This class is made for handling the metadata stored in JSON files.
class Metadata : protected FileUtils
{
	std::string _filename;
	nlohmann::json _document = nullptr;
	Log& _log = Log::Get();

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

	/// @brief Creates new JSON file.
	///	@note If file already exists, it get overwritten.
	void Create() const;

	/// @brief Creates new JSON file using the given filename.
	///	@note If file already exists, it get overwritten.
	void Create(const std::string& filename);

	/// @brief Loads JSON data to the document variable.
	void Load();

	/// @brief Loads JSON data to the document variable using the given filename.
	/// @param filename - Filename of the JSON file.
	void Load(const std::string& filename);

	/// @brief Saves JSON data to the file specified in the filename.
	void Save() const;

	/// @brief Gets JSON Object.
	/// @param name - JSON key.
	nlohmann::json GetJsonObject(const std::string& name);

	/// @brief Sets JSON object.
	/// @param name - JSON key.
	/// @param value - value to set.
	void SetJsonObject(const std::string& name, const nlohmann::json& value);

	/// @brief Gets JSON Array.
	/// @param name - JSON key.
	nlohmann::json GetJsonArray(const std::string& name);

	/// @brief Sets JSON Array.
	/// @param name - JSON key.
	/// @param value - value to set.
	void SetJsonArray(const std::string& name, const nlohmann::json& value);

	/// @brief Gets Boolean.
	/// @param name - JSON key.
	bool GetBool(const std::string& name);

	/// @brief Sets Boolean.
	/// @param name - JSON key.
	/// @param value - value to set.
	void SetBool(const std::string& name, bool value);

	/// @brief Gets Integer.
	/// @param name - JSON key.
	int GetInt(const std::string& name);

	/// @brief Sets Integer.
	/// @param name - JSON key.
	/// @param value - value to set.
	void SetInt(const std::string& name, const int& value);

	/// @brief Gets Double.
	/// @param name - JSON key.
	double GetDouble(const std::string& name);

	/// @brief Sets Double.
	/// @param name - JSON key.
	///	@param value - value to set.
	void SetDouble(const std::string& name, const double& value);

	/// @brief Gets String.
	/// @param name - JSON key.
	std::string GetString(const std::string& name);

	/// @brief Sets String.
	/// @param name - JSON key.
	/// @param value - value to set.
	void SetString(const std::string& name, const std::string& value);

	/// @brief Checks if the value is a Null.
	/// @param name - JSON key.
	bool IsNull(const std::string& name) const;

	/// @brief Sets as a Null.
	/// @param name - JSON key.
	void SetNull(const std::string& name);
};

/// @overload void Create()
/// @overload void Load()
