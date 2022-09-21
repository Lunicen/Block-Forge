#include "Sandbox.h"
#include "World.h"
#include "Camera.h"
#include "Events/HumanInterfaceDevice.h"
//#include "World/WorldGenerator.h"
#include "Model/BlockFaceModel.h"
#include "Utils/FPSCounter.h"
//#include "World/Chunks/Rendring/ChunkHandler.h"


void Sandbox::InitializeGlfw()
{
	glfwInit();

	constexpr auto versionMajor = 3;
	constexpr auto versionMinor = 3;

	// The target version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	HumanInterfaceDevice hid(window);
	Camera camera(window, width, height, glm::vec3(0.0f, 0.0f, 0.0f), hid);

	//auto worldGenerator = std::make_shared<WorldGenerator>(69);

	//ChunkHandler chunkHandler(RenderViewType::cube, 8, 0, camera);
	//chunkHandler.Bind(worldGenerator);
	auto block = Shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");
	auto texture = std::make_shared<Texture>("src/Data/Textures/DirtAtlas.png", 0, 0, 16);
	auto frontVertices = std::vector<Vertex>
	{
		Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
		Vertex{Position{1.0f, 0.0f, 0.0f}, Point{1.0f, 0.0f}},
		Vertex{Position{1.0f, 1.0f, 0.0f}, Point{1.0f, 1.0f}},
		Vertex{Position{0.0f, 1.0f, 0.0f}, Point{0.0f, 1.0f}},
	};

	auto bottomVertices = std::vector<Vertex>
	{
		Vertex{Position{0.0f, 0.0f, 0.0f}, Point{0.0f, 0.0f}},
		Vertex{Position{0.0f, 0.0f, 1.0f}, Point{1.0f, 0.0f}},
		Vertex{Position{1.0f, 0.0f, 1.0f}, Point{1.0f, 1.0f}},
		Vertex{Position{1.0f, 0.0f, 0.0f}, Point{0.0f, 1.0f}},
	};

	texture->SetUvToTextureAtlas(frontVertices);
	texture->SetUvToTextureAtlas(bottomVertices);

	auto frontMesh = std::make_unique<Mesh>
	(
		frontVertices,
		std::vector<TriangleIndexes>
		{
			TriangleIndexes{0, 1, 2},
			TriangleIndexes{2, 3, 0}
		},
		block
	);
	auto bottomMesh = std::make_unique<Mesh>
	(
		bottomVertices,
		std::vector<TriangleIndexes>
		{
			TriangleIndexes{0, 1, 2},
			TriangleIndexes{2, 3, 0}
		},
		block
	);

	texture->Initialize(block);

	auto front = BlockFaceModel(frontMesh, texture);
	auto bottom = BlockFaceModel(bottomMesh, texture);

	FPSCounter counter;
	
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Update();
		camera.HandleInput();
		front.DrawAt(Position(0, 0, 0), camera);
		bottom.DrawAt(Position(0, 0, 0), camera);
		//chunkHandler.Update();
		counter.Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	gltTerminate();
}
