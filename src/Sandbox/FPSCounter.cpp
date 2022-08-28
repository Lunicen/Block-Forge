#include "FPSCounter.h"
#include "GLFW/glfw3.h"
#include <iostream>
using namespace std;

FPSCounter::FPSCounter() {
    this->lastTime = CalculateLastTime();
    this->nbFrames = 0;
    this->actualFps = 60;
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

inline int FPSCounter::GetViewportHeight()const {
    return viewportHeight;
}

inline int FPSCounter::GetViewportWidth() const {
    return viewportWidth;
}

const char*FPSCounter:: GetStr() const {
    return str; 
}

void FPSCounter:: CountFps() {
   
        // Measure speed
        const double currentTime = glfwGetTime();
        nbFrames++;


        if (current_time - lastTime >= 1.0) { 
            this->actualFps = nbFrames;

            nbFrames = 0;
            lastTime += 1.0;
        }

}


