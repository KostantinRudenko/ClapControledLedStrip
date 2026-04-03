#include "Arduino.h"
#include "microphone.h"
#include "timer.h"

uint16_t Microphone::getAmplitude() {
	uint16_t maxV = 0;
	uint16_t minV = 1023;
	static Timer amplitudeTimer;
	uint16_t A;
	amplitudeTimer.reset();

	while (!amplitudeTimer.wait(200)) {
		uint16_t v = analogRead(A1);

		if (maxV < v) maxV = v;
		if (minV > v) minV = v;
	}

	A = maxV - minV;
	return A;
}

bool Microphone::isClap() {
	if (this->getAmplitude() >= 350)
		return true;
	return false;
}
