#pragma once

class EngineException : public std::exception
{
    using Base = exception;

protected:
    explicit EngineException(const std::string& message) : Base(message.c_str()) {}
};

class UninitializedPropertyAccessException final : protected EngineException
{
	using Base = EngineException;

public:
    explicit UninitializedPropertyAccessException(const std::string& message) : Base(message) {}
};