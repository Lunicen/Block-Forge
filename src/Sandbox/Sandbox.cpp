#include "Sandbox.h"
#include "World.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/Shader.h"
#include "Utils/BufferUtils.h"

void Sandbox::Run() const
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!world->IsLoaded())
	{
		log.Error("Cannot start the simulation! The world is not loaded!");
		return;
	}

	GLFWwindow* window = glfwCreateWindow(800, 800, "test", nullptr, nullptr);
	if (window == nullptr)
	{
		log.Error("Failed to create window.");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//    5-------6  
	//   /|      /|   
	//  1-------2 | 
	//  | |     | |   
	//  | 4-----|-7  
	//  |/      |/    
	//  0-------3 
	constexpr GLfloat vertices[24] =
	{
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
		 
		 -0.5f, -0.5f, 1.0f,
		 -0.5f, 0.5f, 1.0f,
		 0.5f,  0.5f, 1.0f,
		 0.5f, -0.5f, 1.0f,
	};

	constexpr GLuint indices[36]
	{
		// front
		0, 1, 2,
		2, 3, 0,

		2, 3, 7,
		7, 6, 2,

		1, 2, 5,
		5, 6, 2,

		0, 4, 1,
		1, 5, 4,

		0, 3, 4,
		4, 7, 3,

		4, 7, 5,
		5, 6, 7
		


	};

	const Shader shader("src/Data/Shaders/Block.vert", "src/Data/Shaders/Block.frag");

	VertexArray vao;
	VertexBuffer vbo(vertices, sizeof(vertices));
	ElementBuffer ebo(indices, sizeof(indices));

	vao.Link(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Load();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
