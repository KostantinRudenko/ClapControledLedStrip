#include <Arduino.h>
#include "FastLED.h"

#include "global.h"
#include "functions.h"
#include "timer.h"

uint8_t deviceSt = 0;
uint8_t currentMode = 0;

Timer clapTimer;

void setup() {
  pinMode(DPIN, OUTPUT);
  pinMode(MPIN, INPUT);

  SetupLedStrip();

  Serial.begin(115200);
}

void loop() {
  switch (deviceSt) {
    case 0:
      static uint16_t A;
      static uint8_t  clapsAmount = 0;
      deviceSt = 1;
      break;

    case 1:
      GetAmplitude(A);

      if (A <= Limit && clapTimer.wait(3000))
        deviceSt = 2;

      if (isClap(A)) {
        clapsAmount++;
        clapTimer.reset();
        Serial.print("Claps = ");
        Serial.println(clapsAmount);
      }
      break;

    case 2:
      Serial.println("Timer end");
      deviceSt = 3;
      break;

    case 3:
      break;

  }
}
