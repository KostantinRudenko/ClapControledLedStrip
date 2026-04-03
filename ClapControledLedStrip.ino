#include <Arduino.h>
#include "FastLED.h"

#include "global.h"
#include "functions.h"
#include "timer.h"
#include "ledStrip.h"
#include "microphone.h"

uint8_t deviceSt = 0;
uint8_t deviceMode = 0;

Timer clapTimer;
LedStrip led;
Microphone micro;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
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
      break;

    case 1:
      clapTimer.reset();
      deviceSt = 2;
      break;

    case 2:

      if (clapsAmount != 0 && clapTimer.wait(WAITING_CLAP_TIME)) {
        deviceSt = 3;
        break;
      }

      if (micro.isClap()) {
        clapsAmount++;
        Serial.print("Claps = ");
        Serial.println(clapsAmount);
        clapTimer.reset();
      }

      deviceSt = 5;
      break;

    case 3:
      //Serial.println("Timer end");
      //deviceSt = clapsAmount + 2;
      deviceSt = 4;
      break;

    case 4:
      led.setMode(clapsAmount);
      clapsAmount = 0;
      deviceSt = 5;
      break;

    case 5:
      if (led.executeMode()) {
        deviceSt = 2;
      }
      break;

    /* case 3:
      Serial.println("Mode 2");
      deviceSt = 0;
      break;
      */

    /* case 4:
      Serial.println("Mode 3");
      deviceSt = 0;
      break;
      */

    /* case 5:
      led.alarmMode();
      //deviceSt = 0;
      break;
      */

    default:
      deviceSt = 0;
      break;
  }
}
