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

void GetAmplitude(uint16_t& A) {
	uint16_t maxV = 0;
	uint16_t minV = 1023;
	uint32_t start = millis();

	while (millis() - start < 100) {
		uint16_t v = analogRead(MPIN);

		if (maxV < v) maxV = v;
		if (minV > v) minV = v;
	}

	A = maxV - minV;
}

bool isClap(uint16_t& A) {
	if (A >= Limit)
		return true;
	return false;
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

bool FillFromColorToColor(const CRGB& FromColor, const CRGB& ToColor) {
	static CRGB curColor = FromColor;

	if (curColor.r < ToColor.r) curColor.r++;
	if (curColor.g < ToColor.g) curColor.g++;
	if (curColor.b < ToColor.b) curColor.b++;

	if (curColor.r > ToColor.r) curColor.r--;
	if (curColor.g > ToColor.g) curColor.g--;
	if (curColor.b > ToColor.b) curColor.b--;

	for (uint8_t i=0; i < LEDSAMOUNT; i++) {
		leds[i] = curColor;
	}
	FastLED.show();

	if (curColor.r == ToColor.r &&
	    curColor.g == ToColor.g &&
	    curColor.b == ToColor.b)
		return true;
	return false;

}
