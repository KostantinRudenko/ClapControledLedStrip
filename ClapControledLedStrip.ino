#include <Arduino.h>
#include "FastLED.h"

#include "global.h"
#include "functions.h"

uint8_t st = 0;
uint8_t clapsAmount = 0;

uint16_t value;
uint16_t A;
uint16_t minV = 1023;
uint16_t maxV = 0;

uint32_t start = 0;
uint32_t clapWaitingStartTime = 0;

bool isClapDetected = false;

void setup() {
  pinMode(DPIN, OUTPUT);
  pinMode(MPIN, INPUT);

  SetupLedStrip();

  Serial.begin(115200);
}

void loop() {
  switch (st) {
    case ClapChecking:
      GetAmplitude(A);

      if (!isClapDetected && A > Limit) {
        clapsAmount++;
        isClapDetected = true;
        clapWaitingStartTime = millis();

        leds[clapsAmount-1] = CRGB(0,0,10);
        FastLED.show();

        Serial.print("Clap detected. New amount: ");
        Serial.println(clapsAmount);
      }

      if (isClapDetected && A < Limit) {
        isClapDetected = false;
        Serial.println("Amplitude is lower than limit");
      }

      if (millis() - clapWaitingStartTime > ClapWaitingTime && clapsAmount != 0) {
        Serial.println("Clearing the strip");
        st = ClearingLed;
      }
      break;

    case ClearingLed:
      ClearStrip();
      st = ClapAnalyzing;
      break;

    case ClapAnalyzing:
      switch (clapsAmount) {
        default:
          st = ClapChecking;
      }
      clapsAmount = 0;
      break;

  }
}
