#include <Arduino.h>
#include "FastLED.h"

#include "global.h"
#include "functions.h"

uint8_t st = 0;
uint8_t curMode = 0;

uint8_t clapsAmount = 0;

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

      static uint16_t A;
      GetAmp(A);

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
        ClearStrip();
        st = ClapAnalyzing;
      }
      else if (clapsAmount == 0)
        st = Executting;

      break;

    case ClapAnalyzing:
      curMode = clapsAmount;
      clapsAmount = 0;
      break;

    case Executting:
      switch (curMode) {}
      st = ClapChecking;
  }
}
