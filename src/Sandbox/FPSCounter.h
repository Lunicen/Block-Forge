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
	GLTtext* _fps;
	double _lastTime;
	int _numberOfFrames;
	int _actualFps;

	void CountFps();

public:

	FPSCounter();

	FPSCounter(const FPSCounter&) = delete;
	FPSCounter(FPSCounter&&) = delete;
	FPSCounter& operator=(const FPSCounter&) = delete;
	FPSCounter& operator=(FPSCounter&&) = delete;

	void Update();

	~FPSCounter();
	
};
