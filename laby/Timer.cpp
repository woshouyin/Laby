#include "Timer.h"
#include <windows.h>

Timer::Timer(int pause) {
	Timer::pause = pause;
	Timer::lastTick = GetTickCount();
}

Timer::~Timer() {

}

bool Timer::Loop() {
	int tick = GetTickCount();
	if (tick - lastTick >= pause) {
		lastTick = tick;
		return true;
	}
	else {
		return false;
	}
}
