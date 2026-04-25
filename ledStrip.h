#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include <Arduino.h>
#include "FastLED.h"
#include "global.h"

class LedStrip {
	private:
		uint8_t _ledPin;
		uint16_t _ledsAmount;
		uint8_t _currentMode;
		CRGB _leds[LEDS_AMOUNT];
	public:
		LedStrip();
		void clear();
		void setMode(uint8_t mode);
		bool executeMode();
		bool fillFromColorToColor(const CRGB& FromColor, const CRGB& ToColor);
		void alarmMode();
		bool blueFillMode();
		void pinkRunnerMode();
};

#endif
