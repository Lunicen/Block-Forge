#pragma once
#include "Hud.h"
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
	std::unique_ptr<Hud> _hud{};

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
		constexpr auto chunkSize = 16;
		constexpr auto renderDistance = 7;

		_camera = std::make_unique<Camera>(window, glm::vec3(0.0f, 20.0f, 0.0f));
		_worldGenerator = std::make_shared<WorldGenerator>(worldSeed);
		_hud = std::make_unique<Hud>();

		_chunkPlacer = std::make_unique<ChunkPlacer>(OrderType::shortOval, chunkSize, renderDistance, _camera->GetPosition());
		_chunkPlacer->Bind(_worldGenerator, chunkSize);
		
		_fpsCounter = std::make_unique<FPSCounter>();
	}

	void OnUpdate() override
	{
		_camera->Update();

		const ChunkRenderer chunkRenderer;
		chunkRenderer.Render(_chunkPlacer->GetChunks(), *_worldGenerator->GetBlockMap().GetBlocksTexture(), *_camera);
		
		_fpsCounter->Update();
		_hud->Draw();
	}
	
	void OnEvent(HumanInterfaceDevice& hid) override
	{
		_camera->HandleInput(hid);
		_chunkPlacer->ReactToCameraMovement(_camera->GetPosition());
		_hud->ChangeSelectedItemSlot(hid);
	}

	~SandboxLayer() override
	{
		_chunkPlacer->Terminate();
		gltTerminate();
	}
};
