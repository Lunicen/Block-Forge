#include "Block.h"

Block::Block(std::string name) : name(std::move(name))
{
}

void Block::SetName(const std::string& name)
{
	this->name = name;
}

std::string Block::GetName() const
{
	return this->name;
}
//lol lmao
