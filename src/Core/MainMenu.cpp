#include "MainMenu.h"
#include"imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


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

void MainMenu::InitializeGlfw()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //(core profile (use only modern functions to hell with old ones))
}


void MainMenu::Draw()
{
	//initialize GLFW
	glfwInit();

	//hints (information about version to glfw) //version 3.3
	InitializeGlfw();

	GLFWwindow* window = glfwCreateWindow(1600, 800, "Main menu", /*glfwGetPrimaryMonitor()*/  nullptr, nullptr); //width, height, name, FULLSCREAN(nullptr/?), "not important"
	//check if window fails to create
	if (window == nullptr)
	{
		std::cout << " Failed to generate GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window); //introduce new window to current context

	gladLoadGL(); //load GLAD so it configures OPENGL
	//glViewport(0, 0, 800, 800); //area of the window for opengl speicfy the viewport from 0 to 800


	///////////////IMGUI/////////////////
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	//Alternatively:
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	//////////////IMGUI///////////////////


	///MAIN WHILE LOOP///
	bool quit = false;
	while (!glfwWindowShouldClose(window) && !quit)
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //rgb, alpha
		glClear(GL_COLOR_BUFFER_BIT);

		//IMGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::SetNextWindowSize(ImVec2(600, 500));


		//For Options:
		//ImGui::Text("Welcome to the Block Forge!");
		//ImGui::Checkbox("Draw Triangle", &drawTriangle);
		//ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		//ImGui::ColorEdit4("Color", color);
		//ImGui::SetCursorPos(ImVec2(20, 20));


		ImGui::Begin("Main Menu");
		DrawCenteredText("Welcome to the Block Forge!");
		DrawWindowSizedButton("PLAY");
		DrawWindowSizedButton("OPTIONS");
		quit = DrawWindowSizedButton("EXIT");

		if(DrawWindowSizedButton("CREDITS"))
		{
			
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		//swap the front buffer with the back buffer
		glfwSwapBuffers(window); 
		//take care of all GLFW EVENTS
		glfwPollEvents(); //process windows events: resize and so on... without this nothing will work
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);
	glfwTerminate();
}
