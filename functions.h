#include "FastLED.h"

void ClearStrip() {
	for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}
