#include "Sandbox.h"
#include "World.h"

#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
#include "World/ChunkManager.h"
#include "World/WorldGenerator.h"
#include "Sandbox/FPSCounter.h"

void Sandbox::InitializeGlfw()
{
	glfwInit();

	// The target version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Sandbox::Run()
{
	constexpr int width = 1280;
	constexpr int height = 720;

	InitializeGlfw();

	if (!_world.IsLoaded())
	{
		_log.Error("Cannot start the simulation! The world is not loaded!");
		return;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, "Block Forge", nullptr, nullptr);
	if (window == nullptr)
	{
		_log.Error("Failed to create window.");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);



	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	HumanInterfaceDevice hid(window);
	Camera camera(window, width, height, glm::vec3(0.0f, 0.0f, 0.0f), hid);
	auto blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

	auto worldGenerator = std::make_shared<WorldGenerator>(69);
	worldGenerator->Initialize(blockShader);

	ChunkManager chunkManager(5, 5, camera);
	chunkManager.Bind(worldGenerator);

	FPSCounter counter;

	while(!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Update();
		camera.HandleInput();
		chunkManager.Update();
		counter.Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	gltTerminate();
}
