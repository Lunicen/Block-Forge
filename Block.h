#pragma once
#include <string>

class Block
{
	std::string name;

public:
	Block() = delete;
	explicit Block(std::string name);

	void SetName(const std::string& name);
	std::string GetName() const;
};

