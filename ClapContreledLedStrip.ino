
#define DPIN 13 // Control Pin
#define MPIN A0 // Microphone Pin
#define Limit 500

enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  CheckClap,
  TurnLedON,
  TurnLedOFF
};

uint8_t st = 0;
uint8_t ledSt = OFF;

uint16_t minV = 1023;
uint16_t maxV = 0;

uint32_t start = 0;

void setup() {
  pinMode(DPIN, OUTPUT);
  pinMode(MPIN, INPUT);

  Serial.begin(115200);
}

void loop() {
  switch (st) {
    case CheckClap:
      minV = 1023;
      maxV = 0;
      start = millis();
      while (millis() - start < 50) {
        uint16_t val = analogRead(A0);
        if (val < minV) minV = val;
        if (val > maxV) maxV = val;

        uint16_t A = maxV - minV;
        Serial.println(A);

        if (A > Limit) {
          if (ledSt == OFF)
            st = TurnLedON;
          else
            st = TurnLedOFF;
        }
      }

      break;

    case TurnLedON:
      digitalWrite(DPIN, ON);
      Serial.println("Led is ON");
      ledSt = ON;
      st = CheckClap;
      break;

    case TurnLedOFF:
      digitalWrite(DPIN, OFF);
      Serial.println("Led is OFF");
      ledSt = OFF;
      st = CheckClap;
      break;
  }
}
