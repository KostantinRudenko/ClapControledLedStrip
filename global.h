
#define LEDSAMOUNT 5

#define DPIN 5 // Control Pin
#define MPIN A0 // Microphone Pin
#define Limit 400
#define ClapWaitingTime 1500

#define MiddleMicroOutValue 268

enum LedStates {
  OFF=0,
  ON
};

enum modes {
  AlarmMode = 3
};

enum deviceStates {
  ClapChecking,
  ClapAnalyzing,
  ModeExecuting,
  ClearingLed
};

CRGB leds[LEDSAMOUNT];

