#pragma once
#include "Core/Log.h"
#include "Structure/Chunk.h"


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
	///	@param blocksTexture - The texture that the blocks are using.
	///	@param chunks - Chunks to render with their positions on the map.
	void Render(const HashMap<Position, std::unique_ptr<Chunk>>& chunks, const TextureAtlas& blocksTexture, const Camera& camera) const;
};


