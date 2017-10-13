#pragma once

class Timer {
public:
	int pause;
	long lastTick;
	Timer(int pause);
	bool Loop();
};