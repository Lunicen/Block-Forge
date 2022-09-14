#pragma once
#include <unordered_map>

#include "Sandbox/Model/BlockModel.h"

template <>
struct std::hash<glm::ivec3>
{
    size_t operator()(const glm::ivec3 &origin) const noexcept
    {
        return std::hash<std::string>()
    	(
			std::to_string(origin.x) + 
			std::to_string(origin.y) + 
			std::to_string(origin.z)
		);
    }
};

class BlocksQueue
{
	struct BlockData
	{
		std::shared_ptr<BlockModel> model;
		FacesVisibility visibility{};
	};
	std::unordered_map<glm::ivec3, BlockData> _blocks;

	void CheckIfKeyExists(const glm::ivec3& origin);

public:

	void Add(const std::shared_ptr<BlockModel>& block, glm::ivec3 origin, FacesVisibility visibilityFlags);
	void Add(const std::shared_ptr<BlockModel>& block, glm::ivec3 origin);

	void Remove(glm::ivec3 origin);

	std::shared_ptr<BlockModel>& GetModel(glm::ivec3 origin);
	FacesVisibility& GetVisibility(glm::ivec3 origin);
};
