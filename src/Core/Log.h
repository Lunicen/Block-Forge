#pragma once
#include "spdlog/spdlog.h"

class Log
{
public:
	static void Init();

	static void Trace(const std::string& message);
	static void Info(const std::string& message);
	static void Warn(const std::string& message);
	static void Error(const std::string& message);
	static void Critical(const std::string& message);
};