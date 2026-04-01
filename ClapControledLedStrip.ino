#include <Arduino.h>
#include "FastLED.h"

#include "global.h"
#include "functions.h"
#include "timer.h"
#include "ledStrip.h"

uint8_t deviceSt = 0;
uint8_t deviceMode = 0;

Timer clapTimer;
LedStrip led;

void setup() {
  pinMode(DPIN, OUTPUT);
  pinMode(MPIN, INPUT);

  Serial.begin(115200);
}

void loop() {
  switch (deviceSt) {
    case 0:
      static uint16_t A;
      static uint8_t  clapsAmount = 0;
      clapTimer.reset();
      deviceSt = 1;
      clapsAmount = 0;
      break;

    case 1:
      GetAmplitude(A);

      if (clapsAmount != 0 && clapTimer.wait(3000))
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
      deviceSt = clapsAmount + 2;
      break;

    case 3:
      Serial.println("Mode 2");
      deviceSt = 0;
      break;

    case 4:
      Serial.println("Mode 3");
      deviceSt = 0;
      break;

    case 5:
      led.alarmMode();
      //deviceSt = 0;
      break;

    default:
      deviceSt = 0;
      break;
  }
}
