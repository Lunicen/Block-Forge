#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <glad/glad.h>

#define GLT_IMPLEMENTATION

#pragma warning(push, 0)
#include <gltext.h>
#pragma warning(pop)

class FPSCounter
{
private:
	GLTtext* fps;
	double lastTime;
	int nbFrames;
	int actualFps;
	const int viewportWidth = 50;
	const int viewportHeight = 100;
	char str[30]{};

public:

	FPSCounter();
	double GetLastTime() const;
	int GetnbFrames() const;
	int GetActualFps();
	double CalculateLastTime() const;
	int GetViewportHeight()const;

	int GetViewportWidth() const;
	const char* GetStr();

	void CountFps();
	void Update();
};