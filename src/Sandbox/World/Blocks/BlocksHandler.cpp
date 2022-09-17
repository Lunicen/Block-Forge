#include "BlocksHandler.h"

#include "Core/EngineExceptions.h"

void BlocksHandler::CheckIfKeyExists(const glm::ivec3& origin)
{
	if (_blocks.find(origin) == _blocks.end())
	{
		throw NotFoundException("This origin is not registered in queue!");
	}
}

void BlocksHandler::Add(const std::shared_ptr<BlockModel>& block, const glm::ivec3 origin, const FacesVisibility visibilityFlags)
{
	_blocks[origin] = BlockData{block, visibilityFlags};
}

void BlocksHandler::Add(const std::shared_ptr<BlockModel>& block, const glm::ivec3 origin)
{
	constexpr FacesVisibility visibilityFlags = {true, true, true, true, true, true};

	_blocks[origin] = BlockData{block, visibilityFlags};
}

void BlocksHandler::Remove(const glm::ivec3 origin)
{
	_blocks.erase(origin);
}

std::shared_ptr<BlockModel>& BlocksHandler::GetModel(const glm::ivec3 origin)
{
	CheckIfKeyExists(origin);

	return _blocks[origin].model;
}

FacesVisibility& BlocksHandler::GetVisibility(const glm::ivec3 origin)
{
	CheckIfKeyExists(origin);

	return _blocks[origin].visibility;
}