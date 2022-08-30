#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#define GLT_IMPLEMENTATION
#pragma warning(push, 0)
#include <gltext.h>
#pragma warning(pop)

class FPSCounter
{
private:

double lastTime;
int nbFrames;
int actualFps;
GLTtext* fps;


public:

	FPSCounter();
	double GetLastTime() const;
	int GetnbFrames() const;
	int GetActualFps();
	double CalculateLastTime() const;

	void CountFps();
	void Update();
	~FPSCounter();
};
