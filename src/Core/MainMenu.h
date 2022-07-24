// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include <string>
#include "Log.h"

#include"imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
// Warning, glfw library MUST be defined at the end!
#include <GLFW/glfw3.h>


class MainMenu
{
private:
	enum class BackgroundStyle
	{
		dark = 0,
		light = 1,
		classic = 2
	};
	Log& log = Log::Get();

	static void DrawCenteredText(const std::string& text);
	static bool DrawWindowSizedButton(const std::string& text);
	static void InitializeGlfw();
	static void InitializeImgui(GLFWwindow*& window);
	static void SetImguiBackgroundStyle(BackgroundStyle backgroundStyle);
	static bool HasWindowFailedToCreate(GLFWwindow*& window);

public:
	void Draw() const;
};

