#pragma once
#include <glm/vec3.hpp>

/// @class ChunkFrame
/// @brief A structure that represents the frame of chunk. It's location and size.
class ChunkFrame
{
public:

	/// @brief Represents the location (origin) of the chunk.
	glm::ivec3 origin;

	/// @brief Size of chunk dimensions.
	size_t size;
};