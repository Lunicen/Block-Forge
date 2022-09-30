#pragma once
#include "ChunkPlacer.h"

/// @class ChunkRenderer
///	@brief Supports rendering chunks.
/// @details This class is responsible for rendering chunks around the camera by using the algorithms
///	specified in the @see Order.
class ChunkRenderer
{
	Log& _log = Log::Get();

public:

	/// @brief The constructor.
	ChunkRenderer();

	/// @brief Renders loaded chunks.
	///	@param camera - A reference to the camera around which the objects are rendered.
	///	@param chunks - Chunks to render with their positions on the map.
	void Render(const std::unordered_map<Position, std::unique_ptr<Chunk>>& chunks, const Camera& camera) const;
};


