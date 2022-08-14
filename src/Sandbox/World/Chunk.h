#pragma once
#include <array>
#include <glm/vec3.hpp>

#include "ChunkManager.h"
class ChunkManager; // Forward declaration

constexpr int chunk_size = 3;

/// @class Chunk
/// @brief Represents a single chunk placed in the world
///	@details This class handles managing the generated chunk in the certain position.
///	@note You should **not** instantiate this class manually. This mechanism is supported by the @ref ChunkManager class.
class Chunk
{
	glm::vec3 _origin{};
	float _midPoint;
	ChunkManager& _chunkManager;

	std::array<
		std::array<
			std::array<std::unique_ptr<Block>, chunk_size>,chunk_size>,chunk_size> _blocks = {{}};

	//bool IsBlockVisibleAt(int x, int y, int z);

public:
	/// @brief The constructor.
	/// @details The chunk on initialization knows it's position, the structure to render (blocks)
	/// and the player position for proper displaying blocks while the player is moving.
	///	@param origin - chunk XYZ position represented in a 3d vector.
	///	@param chunkManager - reference to the manager that handles chunks in the world.
	///	@attention Do **NOT** give the exact origin position You want to have a chunk placed.
	///	In the constructor it's implemented to place them respectively to the chunk size.
	///	If the defined chunk size is 16 and the origin is (1, 1, 1) the real chunk origin will be (16, 16, 16).
	explicit Chunk(glm::vec3 origin, ChunkManager& chunkManager);

	/// @brief Initializes chunk by allocating the memory.
	void Init();

	/// @brief Draws the chunk in the world.
	///	@note Remember to call @ref Init() beforehand.
	void Draw() const;
};

