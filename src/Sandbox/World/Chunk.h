#pragma once
#include <glm/vec3.hpp>

#include "ChunkData.h"
#include "ChunkManager.h"
class ChunkManager; // Forward declaration

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk in the certain position.
///	@note You should **not** instantiate this class manually. This mechanism is supported by the @ref ChunkManager class.
class Chunk
{
	glm::ivec3 _origin{};
	ChunkManager& _chunkManager;
	std::vector<std::vector<std::vector<bool>>> _isVisible = {{}};
	std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> _blocks;

	void DrawBlockIfExists(int x, int y, int z) const;

public:
	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param origin - chunk XYZ position represented in a 3d vector.
	///	@param chunkManager - reference to the manager that handles chunks in the world.
	///	@attention Do **NOT** give the exact origin position You want to have a chunk placed.
	///	In the constructor it's implemented to place them respectively to the chunk size.
	///	If the defined chunk size is 16 and the origin is (1, 1, 1) the real chunk origin will be (16, 16, 16).
	explicit Chunk(glm::ivec3 origin, ChunkManager& chunkManager);

	/// @brief Initializes chunk by allocating the memory.
	///	@param chunkData - reference to the block structure of the chunk.
	void Load(ChunkData& chunkData);

	/// @brief Draws the chunk in the world.
	void Draw() const;

	/// @brief Get the **actual** origin of the chunk.
	glm::ivec3 GetOrigin() const;
};

