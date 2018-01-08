#pragma once

//Hello it is a timer

class Timer {
public:
	int pause;
	long lastTick;
	Timer(int pause);
	bool Loop();
};