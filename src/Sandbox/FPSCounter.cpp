#include "FPSCounter.h"
#include "GLFW/glfw3.h"
#include <iostream>
using namespace std;

FPSCounter::FPSCounter() {
    this->lastTime = CalculateLastTime();
    this->nbFrames = 0;
    this->actualFps = 60;
}

inline double FPSCounter::GetlastTime() const
{
    return lastTime;
}

inline int FPSCounter::GetnbFrames() const
{
    return nbFrames;
}


inline double FPSCounter::CalculateLastTime() {
     return glfwGetTime();
}

int FPSCounter::GetactualFps() const {
    return actualFps;
}

void FPSCounter:: CountFPS() {
   
        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;


        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            this->actualFps = nbFrames;

            nbFrames = 0;
            lastTime += 1.0;
        }

}


