#ifndef MICROPHONE_H
#define MICROPHONE_H
#include "Arduino.h"

class Microphone {
	//private:
		//uint8_t _inPin;
	public:
		//Microphone(uint8_t InPin);
		uint16_t getAmplitude();
		bool isClap();
};

#endif
