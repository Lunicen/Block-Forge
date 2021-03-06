#pragma once
#include <string>

class Block
{
	std::string name;

protected:
	explicit Block(std::string name);

public:
	Block() = delete;
	void SetName(const std::string& name);
	std::string GetName() const;
};

