#include "timer.h"
#include <Arduino.h>

void Timer::reset() {
	_startTime = millis();
}

bool Timer::wait(uint32_t time) {
	if (millis() - _startTime >= time)
		return true;
	return false;
}
