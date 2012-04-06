#define MSP430G2231
#define ARDUINO

#include "libraries/easymsp.h"

void setup()
{
	output(0);
	output(6);
}

void loop()
{
	digitalWrite(0, HIGH);
	digitalWrite(6, LOW);
	millis(500);
	digitalWrite(0, LOW);
	digitalWrite(6, HIGH);
	millis(500);
}