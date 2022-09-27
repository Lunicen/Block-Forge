#pragma once
#include "ChunkPlacer.h"

/// @class ChunkRenderer
///	@brief Supports rendering chunks.
/// @details This class is responsible for rendering chunks around the camera by using the algorithms
///	specified in the @see Order.
class ChunkRenderer
{
	Log& _log = Log::Get();
	ChunkPlacer& _chunkPlacer;

public:

	/// @brief The constructor.
	explicit ChunkRenderer(ChunkPlacer& chunkPlacer);

	/// @brief Renders loaded chunks.
	///	@param camera - A reference to the camera around which the objects are rendered.
	void Render(const Camera& camera) const;
};


