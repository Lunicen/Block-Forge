#include "FPSCounter.h"

#include <string>
#include <GLFW/glfw3.h>

#include "Core/EngineExceptions.h"

FPSCounter::FPSCounter()
{
    if (!gltInit())
	{
		throw BadInitializationException("Failed to initialize GLText library!");
	}

    _lastTime = glfwGetTime();
    _numberOfFrames = 0;
    _actualFps = 0;
    _fps = gltCreateText();
}


void FPSCounter:: CountFps()
{
	const double currentTime = glfwGetTime();
	++_numberOfFrames;


	if (currentTime - _lastTime >= 1.0) {
		_actualFps = _numberOfFrames;

		_numberOfFrames = 0;
		_lastTime += 1.0;
	}
}

void FPSCounter::Update()
{
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gltBeginDraw();

	CountFps();
	const auto text = "FPS: " + std::to_string(_actualFps);
	gltSetText(_fps, text.c_str());

	gltDrawText2DAligned(_fps, 0.0f, 20.0f, 1.0f, GLT_LEFT, GLT_BOTTOM);

	gltEndDraw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
}

FPSCounter::~FPSCounter()
{
    gltDeleteText(_fps);
}


