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

public:

	FPSCounter();
	double GetLastTime() const;
	int GetnbFrames() const;
	int GetActualFps() const;
	static double CalculateLastTime();
	void CountFps();
	void Update();
	~FPSCounter();
};
