#pragma once
#include <string>

#include"imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"

enum class BackgroundStyle
{
	dark = 0,
	light = 1,
	classic = 2
};

class MainMenu
{
private:
	Log& log = Log::Get();

	void DrawCenteredText(const std::string text);
	bool DrawWindowSizedButton(const std::string text);
	void InitializeGlfw();
	void InitializeImgui(GLFWwindow* &window);
	void SetImguiBackgroundStyle(BackgroundStyle backgroundStyle);
	bool HasWindowFailedToCreate(GLFWwindow*& window);
public:
	void Draw();
};

