// ReSharper disable CppUnusedIncludeDirective
#pragma once
#include <string>
#include "core/log.h"

#include "imgui.h"
#include "application/hid/human_interface_device.h"
#include "application/layer/layer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/opengl_headers.h"

/// @class MainMenuLayer
/// @brief Displays the GUI that is a Main Menu.
class MainMenuLayer : public Layer
{
	enum class BackgroundStyle
	{
		dark = 0,
		light = 1,
		classic = 2
	};
	Log& _log = Log::Get();

	static void DrawCenteredText(const std::string& text);
	static bool DrawWindowSizedButton(const std::string& text);
	static void InitializeGlfw();
	static void InitializeImgui(GLFWwindow*& window);
	static void SetImguiBackgroundStyle(BackgroundStyle backgroundStyle);
	static bool HasWindowFailedToCreate(GLFWwindow*& window);

public:

	/// @brief Creates the window and draws the interactive Main Menu.
	void Draw() const;


	void OnUpdate() override
	{

	}

	void OnEvent(HumanInterfaceDevice& hid) override
	{

	}

	MainMenuLayer()
	{
		LockLayer();
	}
};

