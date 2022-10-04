#pragma once
#include <chrono>
#include <iostream>

class Timer  // NOLINT(cppcoreguidelines-special-member-functions)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTimestamp;
	std::string _methodName;

public:
	explicit Timer(std::string whatIsMeasured) : _methodName(std::move(whatIsMeasured))
	{
		_startTimestamp = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		const auto finishTimestamp = std::chrono::high_resolution_clock::now();

		const auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimestamp).time_since_epoch().count();
		const auto end = std::chrono::time_point_cast<std::chrono::microseconds>(finishTimestamp).time_since_epoch().count();

		const auto duration = end - start;
		const double ms = static_cast<double>(duration) * 0.001;

		std::cout << _methodName << ": " << duration << "us (" << ms << "ms)\n";
	}
};

