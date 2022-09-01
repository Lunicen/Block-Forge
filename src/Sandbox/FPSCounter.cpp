#include "FPSCounter.h"

#include <string>
#include <GLFW/glfw3.h>

#include "Utils/EngineExceptions.h"
using namespace std;

FPSCounter::FPSCounter()
{
    if (!gltInit())
	{
		throw BadInitializationException("Failed to initialize GLText library!");
	}

    this->lastTime = CalculateLastTime();
    this->nbFrames = 0;
    this->actualFps = 60;
    this->fps = gltCreateText();

}

inline double FPSCounter::GetLastTime() const
{
    return lastTime;
}

inline int FPSCounter::GetnbFrames() const
{
    return nbFrames;
}

int FPSCounter::GetActualFps()  {
    return actualFps;
}

inline double FPSCounter::CalculateLastTime() const{
     return glfwGetTime();
}


void FPSCounter:: CountFps() {
		
        const double currentTime = glfwGetTime();
        nbFrames++;


        if (currentTime - lastTime >= 1.0) { 
            this->actualFps = nbFrames;

            nbFrames = 0;
            lastTime += 1.0;
        }

}

void FPSCounter::Update()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gltBeginDraw();

	CountFps();
    const auto text = "FPS: " + std::to_string(actualFps);
	gltSetText(fps, text.c_str());

    gltDrawText2DAligned(fps, 0.0f, 20.0f, 1.0f, GLT_LEFT, GLT_BOTTOM);

    gltEndDraw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


