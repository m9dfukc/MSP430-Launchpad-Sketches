#include "libraries/friendly_launchpad.h"

void setup() {
	// initialize the red led as output
	pinMode(10, OUTPUT);
	// initialize the green led as output
	pinMode(16, OUTPUT);
}

void loop() {
	// Flash the lights
	digitalWrite(10, HIGH);  
	digitalWrite(16, LOW);
	delay(2500);
	digitalWrite(10, LOW);  
	digitalWrite(16, HIGH);
	delay(500);
}