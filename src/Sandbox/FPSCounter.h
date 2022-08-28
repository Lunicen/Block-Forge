#pragma once

class FPSCounter
{
private:

double lastTime;
int nbFrames;
int actualFps;
const int viewportWidth = 50;
const int viewportHeight = 100;
char str[30]{};

public:

	FPSCounter();
	double GetLastTime() const;
	int GetnbFrames() const;
	int GetActualFps();
	double CalculateLastTime() const;
	int GetViewportHeight()const;

	int GetViewportWidth() const;
	const char* GetStr() const;

	void CountFps();

};