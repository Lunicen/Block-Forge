#pragma once
#include "spdlog/spdlog.h"

/// @class   Log
/// @brief   Logs the occurred events with additional information and status.
/// @details This static class is made for logging events where actions might contain important messages.
/// Used for tracking control flow, errors, etc.
///	If you need more information about the log levels and when to use them,
///	check out [this](https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels) link.
class Log
{
private:
	Log::Log() {
		spdlog::set_pattern("[%T] [%^%l%$] %v");
		spdlog::set_level(spdlog::level::trace);
		spdlog::info("Logging initialized!");
	}

public:

	Log(const Log&) = delete;

	/// @brief Returns Logger instance
	static Log& Get()
	{
		static Log instance;
		return instance;
	}


	/// @brief Prints tracing message.
	///	@details The trace is used to print EVERYTHING that is happening.
	///	@warning Never, ever use it in production! Only during the development process.
	/// @param message - Information about the event.
	static void Trace(const std::string& message);

	/// @brief Prints debug message.
	///	@details The debug is used to print the information for diagnostics.
	/// @param message - Information about the event.
	static void Debug(const std::string& message);

	/// @brief Prints info message.
	///	@details The info is used to print the general information about occurred events.
	/// @param message - Information about the event.
	static void Info(const std::string& message);

	/// @brief Prints warning message.
	///	@details The warning is used to warn that the occurred event might cause oddities in the future.
	/// @param message - Information about the event.
	static void Warn(const std::string& message);

	/// @brief Prints error message.
	///	@details The error is used to signalize incorrect behaviour that can be handled (for ex. missing data). 
	/// @param message - Information about the event.
	static void Error(const std::string& message);

	/// @brief Prints critical message.
	///	@details The critical is used to print the error that caused a force shutdown of the application.
	/// @param message - Information about the event.
	static void Critical(const std::string& message);
};