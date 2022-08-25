#pragma once

class FPSCounter
{
private:

double lastTime;
int nbFrames;
int actualFps;

public:

	FPSCounter();
	double GetlastTime() const;
	int GetnbFrames() const;
	int GetactualFps()const;

	double CalculateLastTime();
	void CountFPS();

};