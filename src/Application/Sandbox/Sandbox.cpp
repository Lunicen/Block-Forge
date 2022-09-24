#include "Sandbox.h"
#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
#include "World/WorldGenerator.h"
#include "Utils/FPSCounter.h"
#include "World/Chunks/Rendring/ChunkPlacer.h"


Sandbox::Sandbox(Window& window) : _window(window)
{
}

void Sandbox::Run() const
{
	_log.Info("Launching simulation...");

	HumanInterfaceDevice hid(_window.handle);
	Camera camera(_window.handle, _window.width, _window.height, glm::vec3(0.0f, 0.0f, 0.0f), hid);

	auto worldGenerator = std::make_shared<WorldGenerator>(69);

	ChunkPlacer chunkPlacer(RenderViewType::cube, 8, 1, camera);
	chunkPlacer.Bind(worldGenerator);
	
	FPSCounter counter;

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(_window.handle))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Update();
		camera.HandleInput();
		chunkPlacer.Update();
		counter.Update();

		glfwSwapBuffers(_window.handle);
		glfwPollEvents();
	}

	glDisable(GL_DEPTH_TEST);

	gltTerminate();
}
