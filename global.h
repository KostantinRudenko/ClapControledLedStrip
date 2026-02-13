
#define LEDSAMOUNT 5

#define DPIN 5 // Control Pin
#define MPIN A0 // Microphone Pin
#define NoiseLimit 400
#define ClapWaitingTime 1500

enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  ClapChecking,
  ClapAnalyzing,
  ClearingLed,
  TurnLedON,
  TurnLedOFF,
  BlinkLed
};
