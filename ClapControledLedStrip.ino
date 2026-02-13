#include <Arduino.h>
#include "FastLED.h"

#include "global.h"

CRGB leds[LEDSAMOUNT];

uint8_t st = 0;
uint8_t clapsAmount = 0;
uint8_t ledSt = OFF;

uint16_t value;
uint16_t minV = 1023;
uint16_t maxV = 0;

uint32_t start = 0;
uint32_t clapWaitingStartTime = 0;

bool isClapDetected = false;

void setup() {
  pinMode(DPIN, OUTPUT);
  pinMode(MPIN, INPUT);

  FastLED.addLeds<NEOPIXEL, DPIN>(leds, LEDSAMOUNT);

  Serial.begin(115200);
}

void loop() {
  switch (st) {
    case ClapChecking:
      minV = 1023;
      maxV = 0;
      start = millis();
      while (millis() - start < 50) {
        value = analogRead(MPIN);
        if (minV > value) minV = value;
        if (maxV < value) maxV = value;

        uint16_t A = maxV - minV;

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
      }

      if (millis() - clapWaitingStartTime > ClapWaitingTime && clapsAmount != 0) {
        Serial.println("Clearing the strip");
        st = ClearingLed;
      }
      break;

    case ClearingLed:
      for (uint8_t i = 0; i < LEDSAMOUNT; i++) {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      st = ClapAnalyzing;
      break;

    case ClapAnalyzing:
      switch (clapsAmount) {
        case 1:
          if (ledSt == OFF)
            st = TurnLedON;
          else
            st = TurnLedOFF;
          break;
        case 2:
          st = BlinkLed;
          break;
        default:
          st = ClapChecking;
      }
      clapsAmount = 0;
      break;

    case TurnLedON:
      leds[0] = CRGB::Red;
      FastLED.show();
      Serial.println("Led is ON");
      ledSt = ON;
      st = ClapChecking;
      break;

    case TurnLedOFF:
      leds[0] = CRGB::Black;
      FastLED.show();
      Serial.println("Led is OFF");
      ledSt = OFF;
      st = ClapChecking;
      break;
    
    case BlinkLed:
      leds[0] = CRGB::Black;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Red;
      FastLED.show();
      delay(500);
      leds[0] = CRGB::Black;
      FastLED.show();
      st = ClapChecking;
      break;

  }
}
