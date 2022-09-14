#include "BlocksQueue.h"

#include "Core/EngineExceptions.h"

void BlocksQueue::CheckIfKeyExists(const glm::ivec3& origin)
{
	if (_blocks.find(origin) == _blocks.end())
	{
		throw NotFoundException("This origin is not registered in queue!");
	}
}

void BlocksQueue::Add(const std::shared_ptr<BlockModel>& block, const glm::ivec3 origin, const FacesVisibility visibilityFlags)
{
	_blocks[origin] = BlockData{block, visibilityFlags};
}

void BlocksQueue::Add(const std::shared_ptr<BlockModel>& block, const glm::ivec3 origin)
{
	constexpr FacesVisibility visibilityFlags = {true, true, true, true, true, true};

	_blocks[origin] = BlockData{block, visibilityFlags};
}

void BlocksQueue::Remove(const glm::ivec3 origin)
{
	_blocks.erase(origin);
}

std::shared_ptr<BlockModel>& BlocksQueue::GetModel(const glm::ivec3 origin)
{
	CheckIfKeyExists(origin);

	return _blocks[origin].model;
}

FacesVisibility& BlocksQueue::GetVisibility(const glm::ivec3 origin)
{
	CheckIfKeyExists(origin);

	return _blocks[origin].visibility;
}