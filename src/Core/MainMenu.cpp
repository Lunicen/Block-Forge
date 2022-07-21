#include "MainMenu.h"
#include"imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

////(DELETE LATER)////
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";
////////////////////////


void MainMenu::DrawCenteredText(const std::string text)
{
	const auto windowWidth = ImGui::GetWindowSize().x;
	const auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

bool MainMenu::DrawWindowSizedButton(const std::string text)
{

	const auto windowWidth = ImGui::GetWindowSize().x;
	if (ImGui::Button(text.c_str(), ImVec2(windowWidth -15, 50)))
	{
		return true;
	}
	return false;
}


void MainMenu::Draw()
{
	//initialize GLFW
	glfwInit();

	//hints (information about version to glfw) //version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //(core profile (use only modern functions to hell with old ones))


	//Tutorial 1 any cordinates as long as between -1 and 1
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};


	GLFWwindow* window = glfwCreateWindow(1600, 800, "Main menu", /*glfwGetPrimaryMonitor()*/  NULL, NULL); //width, height, name, FULLSCREAN(NULL/?), "not important"
	//check if window fails to create
	if (window == NULL)
	{
		std::cout << " Failed to generate GLFW window" << std::endl;
		glfwTerminate();
		//TODO tutaj poprawiæ
		//return -1;
	}
	glfwMakeContextCurrent(window); //introduce new window to current context


	gladLoadGL(); //load GLAD so it configures OPENGL
	glViewport(0, 0, 800, 800); //area of the window for opengl speicfy the viewport from 0 to 800


	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VAOs & VBOs//reference containers for VAO and VBO//
	//VAO - vertex array object
	//VBO - vertex buffer object
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO); //vao always before vbo
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //postion of vertex attrib, 3 floats
	glEnableVertexAttribArray(0); //position

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	///////////////IMGUI/////////////////
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	//////////////IMGUI///////////////////


	bool quit = false; //sprawdzic czy da sie lepiej
	glUseProgram(shaderProgram);



	///MAIN WHILE LOOP///
	while (!glfwWindowShouldClose(window) && !quit)
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //rgb, alpha
		glClear(GL_COLOR_BUFFER_BIT);

		//IMGUI//
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::SetNextWindowSize(ImVec2(600, 500));
		//end of IMGUI//


		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);


		

		//ImGui::Text("Welcome to the Block Forge!");
		//ImGui::Checkbox("Draw Triangle", &drawTriangle);
		//ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		//ImGui::ColorEdit4("Color", color);

		//ImGui::SetCursorPos(ImVec2(20, 20));

		/*
		if (ImGui::Button("PLAY", ImVec2(350, 50)))
		{

		}
		if (ImGui::Button("OPTIONS", ImVec2(350, 50)))
		{

		}
		if (ImGui::Button("EXIT", ImVec2(350, 50)))
		{
			quit = true;
		}
		*/

		ImGui::Begin("Main Menu");
		DrawCenteredText("Welcome to the Block Forge!");
		DrawWindowSizedButton("PLAY");
		DrawWindowSizedButton("OPTIONS");
		quit = DrawWindowSizedButton("EXIT");

		if(DrawWindowSizedButton("CREDITS"))
		{
			
		}

		ImGui::End();

		glUseProgram(shaderProgram);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		//swap the front buffer with the back buffer
		glfwSwapBuffers(window); 
		//take care of all GLFW EVENTS
		glfwPollEvents(); //process windows event resize and so on... without this nothing will work
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	//TODO potem sprawdzic
	//return 0;
}
