#include <Arduino.h>
#include "ledStrip.h"
#include "global.h"
#include "FastLED.h"

LedStrip::LedStrip() {
	_ledPin = DATA_PIN;
	_ledsAmount = LEDS_AMOUNT;
	_currentMode = 0;
	Serial.print("Amount = ");
	Serial.println(LEDS_AMOUNT);

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, LEDS_AMOUNT);

}

void LedStrip::clear() {
	for (uint8_t i = 0; i < _ledsAmount; i++) {
		_leds[i] = CRGB::Black;
	}
	FastLED.show();
}

void LedStrip::setMode(uint8_t mode) {
	if (_currentMode != mode ||
	   (_currentMode == BlueWave && mode == BlueWave))
		_currentMode = mode;
	else
		_currentMode = NoMode;

	Serial.print("Current mode = ");
	Serial.println(_currentMode);
}

bool LedStrip::executeMode() {
	if (_currentMode == Alarm) {
		alarmMode();
	}
	return true;
}

bool LedStrip::fillFromColorToColor(const CRGB& FromColor, const CRGB& ToColor) {
	static CRGB curColor = FromColor;

	if (curColor.r < ToColor.r) curColor.r++;
	if (curColor.g < ToColor.g) curColor.g++;
	if (curColor.b < ToColor.b) curColor.b++;

	if (curColor.r > ToColor.r) curColor.r--;
	if (curColor.g > ToColor.g) curColor.g--;
	if (curColor.b > ToColor.b) curColor.b--;

	for (uint8_t i=0; i < _ledsAmount; i++) {
		_leds[i] = curColor;
	}
	FastLED.show();

	if (curColor.r == ToColor.r &&
	    curColor.g == ToColor.g &&
	    curColor.b == ToColor.b)
		return true;
	return false;
}

void LedStrip::alarmMode() {
	static uint8_t RedColor = 0;
	static bool isForward = true;

	if (isForward && RedColor <= 240) {
		RedColor = RedColor + 1;
	}
	else
		isForward = false;

	if (!isForward && RedColor > 0) {
		RedColor = RedColor - 1;
	}
	else
		isForward = true;

	for (uint8_t i = 0; i < _ledsAmount; i++) {
		_leds[i] = CRGB(RedColor,0,0);
	}
	FastLED.show();
}
