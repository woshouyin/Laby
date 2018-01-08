#pragma once

//Hello it is a timer 2.0

class Timer {
public:
	int pause;
	long lastTick;
	Timer(int pause);
	bool Loop();