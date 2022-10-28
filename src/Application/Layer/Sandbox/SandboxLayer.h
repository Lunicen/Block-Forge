#pragma once
#include <glm/vec3.hpp>

#include "Application/Layer/Layer.h"
#include "Application/Layer/Sandbox/Camera.h"
#include "Application/Layer/Sandbox/Utils/FPSCounter.h"
#include "Application/Layer/Sandbox/World/WorldGenerator.h"
#include "Application/Layer/Sandbox/World/Chunks/ChunkPlacer.h"
#include "Application/Layer/Sandbox/World/Chunks/ChunkRenderer.h"

/// @class SandboxLayer
///	@brief Represents sandbox that is played as an simulation.
class SandboxLayer final : public Layer
{
	std::unique_ptr<Camera> _camera{};
	std::unique_ptr<ChunkPlacer> _chunkPlacer{};
	std::unique_ptr<FPSCounter> _fpsCounter{};

	std::shared_ptr<WorldGenerator> _worldGenerator;

public:

	SandboxLayer(const SandboxLayer&) = delete;
	SandboxLayer(SandboxLayer&&) = delete;
	SandboxLayer& operator=(const SandboxLayer&) = delete;
	SandboxLayer& operator=(SandboxLayer&&) = delete;

	/// @brief The constructor.
	///	@param window - Reference to the window.
	explicit SandboxLayer(Window& window)
	{
		glEnable(GL_DEPTH_TEST);

		constexpr auto worldSeed = 1337;
		constexpr auto chunkSize = 32;
		constexpr auto renderDistance = 4;

		_camera = std::make_unique<Camera>(window, glm::vec3(0.0f, 20.0f, 0.0f));
		_worldGenerator = std::make_shared<WorldGenerator>(worldSeed);

		_chunkPlacer = std::make_unique<ChunkPlacer>(OrderType::cube, chunkSize, renderDistance, _camera->GetPosition());
		_chunkPlacer->Bind(_worldGenerator, chunkSize);
		
		_fpsCounter = std::make_unique<FPSCounter>();
	}

	void OnUpdate() override
	{
		_camera->Update();

		const ChunkRenderer chunkRenderer;
		auto& chunksRenderingMutex = _chunkPlacer->GetMutex();

		chunksRenderingMutex.lock();
		chunkRenderer.Render(_chunkPlacer->GetChunks(), *_worldGenerator->GetBlockMap().GetBlocksTexture(), *_camera);
		chunksRenderingMutex.unlock();
		
		_fpsCounter->Update();
	}
	
	void OnEvent(HumanInterfaceDevice& hid) override
	{
		_camera->HandleInput(hid);
		_chunkPlacer->ReactToCameraMovement(_camera->GetPosition());
	}

	~SandboxLayer() override
	{
		_chunkPlacer->Terminate();
		gltTerminate();
	}
};
