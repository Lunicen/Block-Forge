#include "core/log.h"


void Log::SetMode(const LogMode mode)
{
	switch(mode)
	{
	case LogMode::trace:
		spdlog::set_level(spdlog::level::trace);
		break;

	case LogMode::debug:
		spdlog::set_level(spdlog::level::debug);
		break;

	case LogMode::normal:
		spdlog::set_level(spdlog::level::info);
		break;
	}
}

void Log::Trace(const std::string& message) const
{
	spdlog::trace(message);
}

void Log::Debug(const std::string& message) const
{
	spdlog::debug(message);
}

void Log::Info(const std::string& message) const
{
	spdlog::info(message);
}

void Log::Warn(const std::string& message) const
{
	spdlog::warn(message);
}

void Log::Error(const std::string& message) const
{
	spdlog::error(message);
}

void Log::Critical(const std::string& message) const
{
	spdlog::critical(message);
}
