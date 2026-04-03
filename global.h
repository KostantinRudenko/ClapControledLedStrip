#ifndef GLOBAL_H
#define GLOBAL_H

// ---------- Led Strip Vlaues ----------

#define DATA_PIN 5

#define LEDS_AMOUNT 5

#define MinColorValue CRGB(0,0,0)
#define MaxBlueValue CRGB(0,0,200)
#define MaxRedValue CRGB(200,0,0)

enum Modes {
	NoMode = 0,
	BlueWave,
	PinkRunner,
	Alarm
};

// ---------- Led Strip Vlaues ----------



// ---------- Microphone Vlaues ----------

#define MPIN A1 // Microphone Pin
#define Limit 400
#define ClapWaitingTime 1500


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
