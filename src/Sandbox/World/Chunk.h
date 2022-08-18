#pragma once
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

	std::vector<std::vector<std::vector<bool>>> _isDisabled = {{}};
	std::vector<std::vector<std::vector<Block*>>> _blocks = {{}};

	void DrawBlockIfExists(int x, int y, int z) const;
	
	void OptimizeCornersOnXY(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxX, const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY);
	void OptimizeCornersOnYZ(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxY, const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ);
	void OptimizeCornersOnXZ(const std::vector<float>& vector, const std::vector<float>& borderSurfaceMaxX, const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ);

	void OptimizeBordersOnX(const std::vector<float>& borderSurfaceMinX, const std::vector<float>& borderSurfaceMaxX);
	void OptimizeBordersOnY(const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY);
	void OptimizeBordersOnZ(const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ);

	// TODO: Implement this feature
	// bool IsBlockVisibleAt(int x, int y, int z);

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
	void Load(const std::vector<std::vector<std::vector<Block*>>>& blocks);

	void Optimize(const std::vector<float>& borderSurfaceMinX, const std::vector<float>& borderSurfaceMaxX,
	              const std::vector<float>& borderSurfaceMinY, const std::vector<float>& borderSurfaceMaxY,
	              const std::vector<float>& borderSurfaceMinZ, const std::vector<float>& borderSurfaceMaxZ);

	/// @brief Draws the chunk in the world.
	///	@note Remember to call @ref Init() beforehand.
	void Draw() const;

	glm::vec3 GetOrigin() const;

	float GetMidpoint() const;
	
};

