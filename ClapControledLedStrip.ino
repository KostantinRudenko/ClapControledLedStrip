
#define DPIN 13 // Control Pin
#define MPIN A0 // Microphone Pin
#define Limit 400
#define ClapWaitingTime 1500

enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  ClapChecking,
  ClapAnalyzing,
  TurnLedON,
  TurnLedOFF,
  BlinkLed
};

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
          Serial.print("Clap detected. New amount: ");
          Serial.println(clapsAmount);
        }

        if (isClapDetected && A < Limit) {
          isClapDetected = false;
          Serial.println("Amplitude is lower than limit");
        }
      }

      if (millis() - clapWaitingStartTime > ClapWaitingTime) {
        st = ClapAnalyzing;
      }
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
      digitalWrite(DPIN, ON);
      Serial.println("Led is ON");
      ledSt = ON;
      st = ClapChecking;
      break;

    case TurnLedOFF:
      digitalWrite(DPIN, OFF);
      Serial.println("Led is OFF");
      ledSt = OFF;
      st = ClapChecking;
      break;
    
    case BlinkLed:
      digitalWrite(DPIN, OFF);
      delay(500);
      digitalWrite(DPIN, ON);
      delay(500);
      digitalWrite(DPIN, OFF);
      st = ClapChecking;
      break;

  }
}
