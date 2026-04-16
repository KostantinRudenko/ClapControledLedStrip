#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class Timer {
	private:
		uint32_t _startTime;

	public:
		bool wait(uint32_t time);
		void reset();
};

#endif
