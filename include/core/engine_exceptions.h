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
class UninitializedPropertyAccessException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that a class member field has not been initialized.
    /// @details Alarms that a class member field has not been initialized before running the method that throws this exception.
    /// @param message - exception message.
    explicit UninitializedPropertyAccessException(const std::string& message) : Base(message) {}
};

/// @class BadInitializationException
/// @brief Exception made for handling failures on class initialization.
class BadInitializationException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that a class member field has failed to initialize.
    /// @details Alarms that a class member field has not initialized properly.
    /// @param message - exception message.
    explicit BadInitializationException(const std::string& message) : Base(message) {}
};

/// @class LibraryBugException
/// @brief Exception made for alerting bugs related to the 3rd libraries.
class LibraryBugException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that a workaround solution must be applied due to the 3rd library bug.
    /// @details This exception should be thrown, if there is an action that might might crash the program 
    /// and it's related to the bugs with 3rd library.
    /// @param message - exception message.
    explicit LibraryBugException(const std::string& message) : Base(message) {}
};

/// @class NotFoundException
/// @brief Exception made for alarming that the requested asset could not be located or is not loaded.
class NotFoundException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alarms that the requested data does not exist in a memory.
    /// @details This exception should be thrown, if the requested asset was not found.
    /// @param message - exception message.
    explicit NotFoundException(const std::string& message) : Base(message) {}
};

/// @class MismatchException
/// @brief Exception made for handling mismatch situations between the expected and current value.
class MismatchException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alerts that the given value does not match the correct pattern that supports it.
    /// @details This exception should be thrown, if the given value mismatches the right data pattern.
    /// @param message - exception message.
    explicit MismatchException(const std::string& message) : Base(message) {}
};

/// @class UnknownValueException
/// @brief Exception made for handling values to which control flow is undefined.
class UnknownValueException final : public EngineException
{
	using Base = EngineException;

public:

    /// @brief Alerts that the given value is not defined for the control flow.
    /// @details This exception should be thrown, if the variable value is crucial for defining the behaviour of the function.
    /// @param message - exception message.
    explicit UnknownValueException(const std::string& message) : Base(message) {}
};