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
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<ChunkPlacer> _chunkPlacer;

	std::shared_ptr<WorldGenerator> _worldGenerator;

public:

	void OnInitialize(size_t screenWidth, size_t screenHeight) override
	{
		_camera = std::make_unique<Camera>(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 0.0f));
		_worldGenerator = std::make_shared<WorldGenerator>(69);

		_chunkPlacer = std::make_unique<ChunkPlacer>(OrderType::diamond, 8, 8, _camera->GetPosition());
		_chunkPlacer->Bind(_worldGenerator);
	}

	void OnUpdate() override
	{
		const ChunkRenderer chunkRenderer;
		FPSCounter counter;

		_camera->Update();

		_chunkPlacer->Update(_camera->GetPosition());
		chunkRenderer.Render(_chunkPlacer->GetChunks(), *_camera);

		counter.Update();
	}
	
	void OnEvent(InputEvent& inputEvent) override
	{
		_camera->HandleInput(inputEvent);
	}

	void OnEvent(WindowEvent& windowEvent) override
	{
		_camera->UpdateViewport(windowEvent);
	}

	void OnDestroy() override;
};
