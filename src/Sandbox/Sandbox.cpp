#include "Sandbox.h"
#include "World.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Block.h"
#include "Blocktest.h"
#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
#include "Utils/Shader.h"
#include "Utils/BufferUtils.h"

constexpr int width = 800;
constexpr int height = 800;

void Sandbox::InitializeGlfw()
{
	glfwInit();

	// The target version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Sandbox::Run() const
{
	constexpr int width = 800;
	constexpr int height = 800;


	InitializeGlfw();

	if (!_world->IsLoaded())
	{
		_log.Error("Cannot start the simulation! The world is not loaded!");
		return;
	}


	GLFWwindow* window = glfwCreateWindow(width, height, "test", nullptr, nullptr);
	if (window == nullptr)
	{
		_log.Error("Failed to create window.");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);


	Shader shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

	auto block1 = new Block(1, 1, 1);
	auto block2 = new Block(2, 2, 2);

	HumanInterfaceDevice hid(window);
	Camera camera(window, width, height, glm::vec3(0.0f, 0.0f, 2.0f), hid);


	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Load();
		camera.HandleInput();
		camera.AddToShader(shader, "camera");

		block1->Draw();
		block2->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
