#include <Arduino.h>
#include "ledStrip.h"
#include "timer.h"
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
	else if (_currentMode == PinkRunner) {
		pinkRunnerMode();
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
	static uint8_t RedColor = MinAlarmValue.r;
	static bool isForward = true;

	if (isForward && RedColor <= MaxAlarmValue.r) {
		RedColor = RedColor + ALARM_COLOR_CHANGE_DELTA;
	}
	else
		isForward = false;

	if (!isForward && RedColor > MinAlarmValue.r) {
		RedColor = RedColor - ALARM_COLOR_CHANGE_DELTA;
	}
	else
		isForward = true;

	for (uint8_t i = 0; i < _ledsAmount; i++) {
		_leds[i] = CRGB(RedColor,0,0);
	}
	FastLED.show();
}

void LedStrip::pinkRunnerMode() {
	static uint8_t curPos = 0;
	static Timer timer;

	//clear();

	_leds[curPos] = PinkColor2;
	_leds[(curPos+1)%_ledsAmount] = PinkColor1;
	_leds[(curPos+2)%_ledsAmount] = PinkColor0;
	_leds[(curPos+3)%_ledsAmount] = PinkColor1;
	_leds[(curPos+4)%_ledsAmount] = PinkColor2;

	if (timer.wait(111)) {
		_leds[curPos] = CRGB::Black;
		curPos=(curPos+1)%_ledsAmount;
		timer.reset();				
		return;
	}

	FastLED.show();
}
