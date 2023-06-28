#include "application/main_menu_layer.h"

void MainMenuLayer::DrawCenteredText(const std::string& text)
{
	const auto windowWidth = ImGui::GetWindowSize().x;
	const auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::TextUnformatted(text.c_str());
}

bool MainMenuLayer::DrawWindowSizedButton(const std::string& text)
{
	const auto xButtonSize = ImGui::GetWindowSize().x - 15;

	if (constexpr auto yButtonSize = 50; ImGui::Button(text.c_str(), ImVec2(xButtonSize, yButtonSize)))
	{
		return true;
	}
	return false;
}

void MainMenuLayer::InitializeGlfw()
{
	glfwInit();

	constexpr auto versionMajor = 3;
	constexpr auto versionMinor = 3;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void MainMenuLayer::InitializeImgui(GLFWwindow* &window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	const ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void MainMenuLayer::SetImguiBackgroundStyle(const BackgroundStyle backgroundStyle)
{
	switch (backgroundStyle)
	{
	using enum BackgroundStyle;

	case dark:
		ImGui::StyleColorsDark();
		break;

	case light:
		ImGui::StyleColorsLight();
		break;

	case classic:
		ImGui::StyleColorsClassic();
		break;
	}
}

bool MainMenuLayer::HasWindowFailedToCreate(GLFWwindow* &window)
{
	return window == nullptr;
}


void MainMenuLayer::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Main Menu");

	SetImguiBackgroundStyle(BackgroundStyle::dark);
	DrawCenteredText("Welcome to the Block Forge!");

	if(DrawWindowSizedButton("EXIT"))
	{
		// Missing implementation. Probably would be added in the future...
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

