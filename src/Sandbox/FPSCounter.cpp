#include "FPSCounter.h"

#include <string>
#include <GLFW/glfw3.h>

#include "Utils/EngineExceptions.h"

FPSCounter::FPSCounter()
{
    if (!gltInit())
	{
		throw BadInitializationException("Failed to initialize GLText library!");
	}

    this->_lastTime = glfwGetTime();
    this->_numberOfFrames = 0;
    this->_actualFps = 60;
    this->_fps = gltCreateText();

}


void FPSCounter:: CountFps() {
		
        const double currentTime = glfwGetTime();
        ++_numberOfFrames;


        if (currentTime - _lastTime >= 1.0) {
            this->_actualFps = _numberOfFrames;

            _numberOfFrames = 0;
            _lastTime += 1.0;
        }

}

void FPSCounter::Update()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gltBeginDraw();

	CountFps();
    const auto text = "FPS: " + std::to_string(_actualFps);
	gltSetText(_fps, text.c_str());

    gltDrawText2DAligned(_fps, 0.0f, 20.0f, 1.0f, GLT_LEFT, GLT_BOTTOM);

    gltEndDraw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

FPSCounter::~FPSCounter()
{
    gltDeleteText(_fps);
}


