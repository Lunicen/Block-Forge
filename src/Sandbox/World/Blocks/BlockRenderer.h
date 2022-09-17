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

struct BlockVisibility
{
	std::shared_ptr<BlockModel> model;
	FacesVisibility visibility{true, true, true, true, true, true};

	BlockVisibility() = default;

	BlockVisibility(const BlockVisibility&) = default;
	BlockVisibility(BlockVisibility&&) = default;

	BlockVisibility& operator=(const BlockVisibility&) = default;
	BlockVisibility& operator=(BlockVisibility&&) = default;

	~BlockVisibility() = default;
};

class BlockRenderer
{
public:
    void Render(const std::unordered_map<glm::ivec3, BlockVisibility>& blocks);
};

