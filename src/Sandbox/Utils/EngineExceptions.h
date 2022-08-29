#pragma once

/// @class EngineException
/// @brief Wrapper for exceptions dedicated to the engine functionality.
/// @note This class should be inherited for all the defined exceptions related to the engine.
class EngineException : public std::exception
{
    using Base = exception;

protected:

    /// @brief Base method for throwing the message content of the specified exception.
    /// @param message - exception message.
    explicit EngineException(const std::string& message) : Base(message.c_str()) {}
};

/// @class UninitializedPropertyAccessException
/// @brief Exception made for handling uninitialized data situations.
class UninitializedPropertyAccessException final : protected EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that a class member field has not been initialized.
    /// @details Alarms that a class member field has not been initialized before running the method that throws this exception.
    /// @param message - exception message.
    explicit UninitializedPropertyAccessException(const std::string& message) : Base(message) {}
};

class LibraryBugException final : protected EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that a workaround solution must be applied due to the 3rd library bug.
    /// @details This exception should be thrown, if there is an action that might might crash the program 
    /// and it's related to the bugs with 3rd library.
    /// @param message - exception message.
    explicit LibraryBugException(const std::string& message) : Base(message) {}
};