
#define LEDSAMOUNT 5

#define DPIN 5 // Control Pin
#define MPIN A0 // Microphone Pin
#define Limit 400
#define ClapWaitingTime 1500

#define MinBlueValue 0
#define MaxBlueValue 150
#define BlueValueDelta 1

enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  ClapChecking,
  ClapAnalyzing,
  Executting
};

enum modes {
  BlueColorMode = 1,
  PinkWaveMode,
  RedAlarmMode,
  BlueColorDown
};

CRGB leds[LEDSAMOUNT];

