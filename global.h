#ifndef GLOBAL_H
#define GLOBAL_H

// ---------- Led Strip Vlaues ----------

#define DATA_PIN 5

#define LEDS_AMOUNT 5

#define MinColorValue CRGB(0,0,0)
#define MaxBlueValue CRGB(0,0,200)

#define MinAlarmValue CRGB(100,0,0)
#define MaxAlarmValue CRGB(240,0,0)
#define ALARM_COLOR_CHANGE_DELTA 50

enum Modes {
	NoMode = 0,
	BlueWave,
	PinkRunner,
	Alarm
};

// ---------- Led Strip Vlaues ----------



// ---------- Microphone Vlaues ----------

#define MPIN A1 // Microphone Pin
#define AMPLITUDE_LIMIT 375
#define WAITING_CLAP_TIME 3000
#define AMPLITUDE_DETECT_TIME 110

// ---------- Microphone Vlaues ----------


enum LedStates {
  OFF=0,
  ON
};

enum deviceStates {
  WaitClaps,
  AnalyzeClaps,
  ExecuteMode
};


#endif
