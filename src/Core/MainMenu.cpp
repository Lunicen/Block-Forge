#include "MainMenu.h"


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
	//version 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void MainMenu::InitializeImgui(GLFWwindow* &window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void MainMenu::SetImguiBackgroundStyle(BackgroundStyle backgroundStyle)
{
	switch (backgroundStyle)
	{
	case BackgroundStyle::dark:
		ImGui::StyleColorsDark();
		break;

	case BackgroundStyle::light:
		ImGui::StyleColorsLight();
		break;

	case BackgroundStyle::classic:
		ImGui::StyleColorsClassic();
		break;
	}
}

bool MainMenu::HasWindowFailedToCreate(GLFWwindow * &window)
{
	return window == nullptr;
}


void MainMenu::Draw()
{
	InitializeGlfw();

	//In the future window should open in fullscreen OR/AND in window
	//monitor: /*glfwGetPrimaryMonitor()*/
	GLFWwindow* window = glfwCreateWindow(1600, 800, "Main menu", nullptr, nullptr); 
	
	if (HasWindowFailedToCreate(window))
	{
		log.Critical("Main Menu failed to generate GLFW window!");
		glfwTerminate();

	}

	glfwMakeContextCurrent(window);

	InitializeImgui(window);

	gladLoadGL();


	bool quit = false;
	while (!glfwWindowShouldClose(window) && !quit)
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Main Menu");


		SetImguiBackgroundStyle(BackgroundStyle::dark);

		DrawCenteredText("Welcome to the Block Forge!");

		if(DrawWindowSizedButton("PLAY"))
		{
			//TODO 
		}

		if(DrawWindowSizedButton("OPTIONS"))
		{
			//TODO
		}

		if(DrawWindowSizedButton("EXIT"))
		{
			//TODO ASK user whether to close
			quit = true;
		}

		if(DrawWindowSizedButton("CREDITS"))
		{
			//TODO
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		glfwSwapBuffers(window);  	//this swaps buffers without them them new frame will not be loaded
		glfwPollEvents();			//process windows events: resize and so on... without this nothing will work
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);
	glfwTerminate();
}
