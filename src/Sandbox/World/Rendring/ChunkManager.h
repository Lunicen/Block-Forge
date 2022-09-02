#pragma once
#include "Sandbox/Camera.h"
#include "ChunkRenderer.h"
#include "RenderViews/RenderViewTypes.h"

/// @class ChunkManager
/// @brief Handles managing the chunks around the camera.
///	@details This class handles @ref Chunk objects and manages them for optimal experience.
class ChunkManager
{
	Log& _log = Log::Get();

	std::unique_ptr<ChunkRenderer> _renderer;
	Camera& _camera;
	
	size_t _renderDistance;
	size_t _chunkSize;
	RenderViewType _viewType;

	std::unique_ptr<RenderView> GetRenderView(RenderViewType viewType);

public:

	/// @brief The constructor.
	///	@param chunkSize - the size of the generated chunks
	///	@param renderDistance - specifies the maximum distance from the camera to render.
	///	@param camera - the object around which the chunks are rendered.
	ChunkManager(RenderViewType viewType, size_t chunkSize, size_t renderDistance, Camera& camera);

	/// @brief Updates the chunk manager to adapt to the current frame.
	void Update() const;

	/// @brief Binds world generator to the chunk manager.
	///	@details The world generator is used to define how the world is generated, when
	///	this class handles only displaying it in an optimal way.
	///	@param worldGenerator - reference to the world generator.
	void Bind(const std::shared_ptr<WorldGenerator>& worldGenerator);
};

