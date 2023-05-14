#include "application/layer/sandbox/utils/fps_counter.h"

#include <string>
#include "core/engine_exceptions.h"
#include "core/open_gl_headers.h"

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
	gltBeginDraw();

	CountFps();
	const auto text = "FPS: " + std::to_string(_actualFps);
	gltSetText(_fps, text.c_str());

	gltDrawText2DAligned(_fps, 0.0f, 0.0f, 1.0f, GLT_LEFT, GLT_TOP);

	gltEndDraw();
}

FPSCounter::~FPSCounter()
{
    gltDeleteText(_fps);
}


