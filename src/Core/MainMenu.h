#pragma once
#include <string>

class MainMenu
{
private:
	void DrawCenteredText(const std::string text);
	bool DrawWindowSizedButton(const std::string text);
	void InitializeGlfw();
public:
	void Draw();
};

