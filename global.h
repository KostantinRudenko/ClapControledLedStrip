
#define LEDSAMOUNT 30

#define DPIN 5 // Control Pin
#define MPIN A1 // Microphone Pin
#define Limit 400
#define ClapWaitingTime 1500

#define MinColorValue CRGB(0,0,0)
#define MaxBlueValue CRGB(0,0,200)
#define MaxRedValue CRGB(200,0,0)
#define BlueValueDelta 1

enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  WaitClaps,
  AnalyzeClaps,
  ExecuteMode
};

enum modes {
  BlueColorMode = 1,
  PinkWaveMode,
  RedAlarmMode,
  BlueColorDown
};

CRGB leds[LEDSAMOUNT];

