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

void GetAmp(uint16_t& A) {
	uint16_t maxV = 0;
	uint16_t minV = 1023;
	uint32_t start = millis();

	while (millis() - start < 20) {
		uint16_t v = analogRead(MPIN);

		if (maxV < v) maxV = v;
		if (minV > v) minV = v;
	}

	A = maxV - minV;
	Serial.println(A);
}

void AlarmModeFunction() {
	static uint8_t RedColor = 0;
	static bool isForward = true;

	if (isForward && RedColor <= 240) {
		RedColor = RedColor + 10;
	}
	else
		isForward = false;

	if (!isForward && RedColor > 0) {
		RedColor = RedColor - 10;
	}
	else
		isForward = true;

	for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
		leds[i] = CRGB(RedColor,0,0);
	}
	FastLED.show();
}

bool ColorFillUp(const CRGB& MaxValue) {
	static CRGB curColor = CRGB(0,0,0);
	
	if (curColor.r < MaxValue.r) curColor.r++;
	if (curColor.g < MaxValue.g) curColor.g++;
	if (curColor.b < MaxValue.b) curColor.b++;

	for (uint8_t i=0; i < LEDSAMOUNT; i++) {
		leds[i] = curColor;
	}

	FastLED.show();

	if (curColor == MaxValue)
		return true;
	return false;

}

bool ColorFillDown(const CRGB& MinValue) {
	static CRGB curColor = leds[0];
	
	if (curColor.r > MinValue.r) curColor.r--;
	if (curColor.g > MinValue.g) curColor.g--;
	if (curColor.b > MinValue.b) curColor.b--;

	for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
		leds[i] = curColor;
	}

	FastLED.show();

	if (curColor == MinValue)
		return true;
	return false;
}
