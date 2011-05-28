#include "libraries/easymsp.h"

void main(void)
{
	easysetup(void); //Calling easysetup setups the MSP430 for use with EasyMSP. 
	//It is required to call easysetup or EasyMSP will not work properly.
	//easysetup() will automatically call your loop code.
}

void loop(void)
{
	makeHigh(0); //Make P1.0 High (Red LED)
	delayMs(2300); //Pause 2300mS
	makeLow(0); // Make P1.0 Low (Red LED)
	delayMs(500); //Pause 500ms
}