#pragma once

class FPSCounter
{
private:

double lastTime;
int nbFrames;

public:

	FPSCounter();
	double GetlastTime() const;
	int GetnbFrames() const;

	double CalculateLastTime();
	void CountFPS();

};