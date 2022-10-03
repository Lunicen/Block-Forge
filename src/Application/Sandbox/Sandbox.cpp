#include "Sandbox.h"

#include "Camera.h"
#include "World/WorldGenerator.h"
#include "Utils/FPSCounter.h"
#include "World/Chunks/ChunkPlacer.h"


Sandbox::Sandbox(Window& window) : _window(window)
{
}

void Sandbox::Run() const
{
	_log.Info("Launching simulation...");

	//HID hid(_window);
	//Camera camera(_window, glm::vec3(0.0f, 0.0f, 0.0f));

	auto worldGenerator = std::make_shared<WorldGenerator>(69);

	//ChunkPlacer chunkPlacer(OrderType::diamond, 8, 8, camera.GetPosition());
	//chunkPlacer.Bind(worldGenerator);

	// ReSharper disable once CppTooWideScope
	//ChunkRenderer chunkRenderer;
	FPSCounter counter;

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(_window.GetHandle()))
	{

		

		if (_window.GetWidth() <= 0 || _window.GetHeight() <= 0)
		{
			continue;
		}

		

		//camera.Update();
		//camera.HandleInput();

		//chunkPlacer.Update(camera.GetPosition());
		//chunkRenderer.Render(chunkPlacer.GetChunks(), camera);

		counter.Update();

		
	}

	glDisable(GL_DEPTH_TEST);

	gltTerminate();
}
