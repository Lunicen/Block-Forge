#pragma warning(disable : 4267)


#include "Sandbox.h"
#include "World.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLT_IMPLEMENTATION

#include <gltext.h>
#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
#include "World/ChunkManager.h"
#include "World/WorldGenerator.h"
#include <Sandbox/FPSCounter.h>

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

	

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	HumanInterfaceDevice hid(window);
	Camera camera(window, width, height, glm::vec3(0.0f, 0.0f, 0.0f), hid);
	auto blockShader = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

	auto worldGenerator = std::make_shared<WorldGenerator>(69);
	worldGenerator->Initialize(blockShader);

	ChunkManager chunkManager(5, 5, camera);
	chunkManager.Bind(worldGenerator);

	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
	}

	GLTtext* text1 = gltCreateText();
	gltSetText(text1, "Hello World!");

	GLTtext* text2 = gltCreateText();

	int viewportWidth =100, viewportHeight =50;
	double time =1.0;
	char str[30];
	FPSCounter counter;
	
	
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
		time = glfwGetTime();

		glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		glViewport(0, 0, viewportWidth, viewportHeight);
		glClear(GL_COLOR_BUFFER_BIT);


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(text1, 0.0f, 0.0f, 1.0f); // x=0.0, y=0.0, scale=1.0

		gltDrawText2DAligned(text1,
			(GLfloat)(viewportWidth / 2),
			(GLfloat)(viewportHeight / 2),
			3.0f,
			GLT_CENTER, GLT_CENTER);

		sprintf_s(str, "Time: %.4f", time);
		gltSetText(text2, str);

		gltColor(
			cosf((float)time) * 0.5f + 0.5f,
			sinf((float)time) * 0.5f + 0.5f,
			1.0f,
			1.0f);

		gltDrawText2DAligned(text2, 0.0f, (GLfloat)viewportHeight, 1.0f, GLT_LEFT, GLT_BOTTOM);

		gltEndDraw();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		camera.Update();
		camera.HandleInput();
		chunkManager.Update();

		counter.CountFPS();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	gltDeleteText(text1);
	gltDeleteText(text2);


	glfwDestroyWindow(window);
	glfwTerminate();

	gltTerminate();
}
