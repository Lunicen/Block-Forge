#pragma once
#include <chrono>
#include <iostream>

/// @class Timer
///	@brief A debugging tool made for measuring time performance of the
///	segments of code. Purely for benchmarking.
/// @warning This method should **NOT** be in the production code. Use it only for testing!!!
class Timer  // NOLINT(cppcoreguidelines-special-member-functions)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> _startTimestamp;
	std::string _methodName;

public:

	/// @brief The constructor.
	///	@param whatIsMeasured - name of the context that is measured.
	explicit Timer(std::string whatIsMeasured) : _methodName(std::move(whatIsMeasured))
	{
		_startTimestamp = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		const auto finishTimestamp = std::chrono::high_resolution_clock::now();

		const auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(_startTimestamp).time_since_epoch().count();
		const auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(finishTimestamp).time_since_epoch().count();

		std::cout << _methodName << ": " << end - start << "ms\n";
	}
};

