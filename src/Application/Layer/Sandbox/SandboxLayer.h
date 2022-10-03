#pragma once
#include <glm/vec3.hpp>

#include "Application/Layer/Layer.h"
#include "Application/Sandbox/Camera.h"
#include "Application/Sandbox/Utils/FPSCounter.h"
#include "Application/Sandbox/World/WorldGenerator.h"
#include "Application/Sandbox/World/Chunks/ChunkPlacer.h"
#include "Application/Sandbox/World/Chunks/ChunkRenderer.h"

class SandboxLayer final : public Layer
{
	std::unique_ptr<Camera> _camera{};
	std::unique_ptr<ChunkPlacer> _chunkPlacer{};
	std::unique_ptr<FPSCounter> _fpsCounter{};

	std::shared_ptr<WorldGenerator> _worldGenerator;

public:

	explicit SandboxLayer(size_t screenWidth, size_t screenHeight, HumanInterfaceDevice& hid)
	{
		glEnable(GL_DEPTH_TEST);

		_camera = std::make_unique<Camera>(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 0.0f), hid);
		_worldGenerator = std::make_shared<WorldGenerator>(69);

		_chunkPlacer = std::make_unique<ChunkPlacer>(OrderType::diamond, 8, 3, _camera->GetPosition());
		_chunkPlacer->Bind(_worldGenerator);

		_fpsCounter = std::make_unique<FPSCounter>();
	}

	void OnUpdate() override
	{
		const ChunkRenderer chunkRenderer;

		_camera->Update();

		_chunkPlacer->Update(_camera->GetPosition());
		chunkRenderer.Render(_chunkPlacer->GetChunks(), *_camera);

		_fpsCounter->Update();
	}
	
	void OnEvent(KeyboardEvent& keyboardEvent) override
	{
		_camera->HandleInput(keyboardEvent);
	}

	void OnEvent(WindowEvent& windowEvent) override
	{
		_camera->UpdateViewport(windowEvent);
	}

	void OnEvent(MouseEvent& mouseEvent) override
	{
		_camera->HandleInput(mouseEvent);
	}

	~SandboxLayer() override
	{
		gltTerminate();
	}

	
};
