#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include <Arduino.h>
#include "FastLED.h"
#include "ledStripGlobal.h"

class LedStrip {
	private:
		uint8_t _ledPin;
		uint16_t _ledsAmount;
		CRGB _leds[LEDS_AMOUNT];
	public:
		LedStrip();
		void clear();
		bool fillFromColorToColor(const CRGB& FromColor, const CRGB& ToColor);
		void alarmMode();
		bool blueFillMode();
};

#endif
