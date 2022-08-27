#pragma once

class FPSCounter
{
private:

double lastTime;
int nbFrames;
int actualFps;
const int viewportWidth = 50;
const int viewportHeight = 100;
char str[30];

public:

	FPSCounter();
	double GetlastTime() const;
	int GetnbFrames() const;
	int GetactualFps();
	double CalculateLastTime() const;
	int GetviewportHeight()const;

	int GetviewportWidth() const;
	const char* GetStr() const;

	void CountFPS();

};