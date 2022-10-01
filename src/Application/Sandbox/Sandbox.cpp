#include "Sandbox.h"

#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
#include "World/WorldGenerator.h"
#include "Utils/FPSCounter.h"
#include "World/Chunks/ChunkPlacer.h"
#include "World/Chunks/ChunkRenderer.h"


Sandbox::Sandbox(Window& window) : _window(window)
{
}

void Sandbox::Run() const
{
	_log.Info("Launching simulation...");

	HumanInterfaceDevice hid(_window.GetHandle());
	Camera camera(_window, glm::vec3(0.0f, 0.0f, 0.0f), hid);

	auto worldGenerator = std::make_shared<WorldGenerator>(69);

	ChunkPlacer chunkPlacer(OrderType::diamond, 8, 8, camera.GetPosition());
	chunkPlacer.Bind(worldGenerator);

	// ReSharper disable once CppTooWideScope
	ChunkRenderer chunkRenderer;
	FPSCounter counter;

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(_window.GetHandle()))
	{
		glfwPollEvents();

		if (_window.GetWidth() <= 0 || _window.GetHeight() <= 0)
		{
			continue;
		}

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Update();
		camera.HandleInput();

		chunkPlacer.Update(camera.GetPosition());
		chunkRenderer.Render(chunkPlacer.GetChunks(), camera);

		counter.Update();

		glfwSwapBuffers(_window.GetHandle());
	}

	glDisable(GL_DEPTH_TEST);

	gltTerminate();
}
