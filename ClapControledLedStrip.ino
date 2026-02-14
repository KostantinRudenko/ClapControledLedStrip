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
bool isFilledWithBlue = false;

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
        ClearStrip();
        clapsAmount++;
        isClapDetected = true;
        clapWaitingStartTime = millis();

        for (uint8_t i = 0; i < clapsAmount; i++) {
          leds[i] = CRGB(0,0,10);
        }
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
      if (curMode != clapsAmount)
        curMode = clapsAmount;
      else
        curMode = 0;

      clapsAmount = 0;
      st = Executting;
      break;

    case Executting:
      switch (curMode) {
        case RedAlarmMode:
          AlarmModeFunction();
          break;
        case BlueColorMode:
          if (isFilledWithBlue) {
            Serial.println("Going to filling down the strip");
            curMode = BlueColorDown;
            break;
          }

          if (BlueColorFillUp()) {
            isFilledWithBlue = true;
            curMode = 0;
            Serial.println("Strip is filled up");
          }
          break;
        case BlueColorDown:
          if (BlueColorFillDown()) {
            curMode = ClapChecking;
            isFilledWithBlue = false;
            Serial.println("Strip is filled down");
          }
          break;
      }
      st = ClapChecking;
  }
}
