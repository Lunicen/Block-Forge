#include "Log.h"


void Log::Trace(const std::string& message)
{
	spdlog::trace(message);
}

void Log::Debug(const std::string& message)
{
	spdlog::debug(message);
}

void Log::Info(const std::string& message)
{
	spdlog::info(message);
}

void Log::Warn(const std::string& message)
{
	spdlog::warn(message);
}

void Log::Error(const std::string& message)
{
	spdlog::error(message);
}

void Log::Critical(const std::string& message)
{
	spdlog::critical(message);
}
