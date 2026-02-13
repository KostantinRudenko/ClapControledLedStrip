#include "FastLED.h"

void SetupLedStrip() {
	FastLED.addLeds<NEOPIXEL, DPIN>(leds, LEDSAMOUNT);
}

void ClearStrip() {
	for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
		leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void GetAmplitude(uint16_t& Amplitude) {
	uint16_t maxV = 0;
	uint16_t minV = 1023;

	uint32_t start = millis();

	while (millis() - start < 20) {
		int16_t value = analogRead(MPIN);

		if (maxV < value) maxV = value;
		if (minV > value) minV = value;
	}
	Amplitude = maxV - minV;
}

void AlarmMode() {
	static uint8_t RedColor = 0;

	for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
		leds[i] = CRGB(RedColor,0,0);
	}

	if (RedColor <= 240)
		RedColor = RedColor + 15;
	else
		RedColor = RedColor - 15;

	FastLED.show();
}
