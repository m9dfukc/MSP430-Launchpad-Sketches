/* LED p1.0 & p1.6 toggle example */

#include "libraries/easymsp.h"
#include <stdio.h>

easymsp

unsigned int status;
unsigned int toggle;
int counter;

void main()
{
	stopwd();
	setFreq(M8);
	
	output(0);
	output(6);
	input(3);
	
	status = 0;
	toggle = 0;
	counter = 0;
	
	while (1) 
	{
		loop();
	}
}

void loop()
{
	status = read(3);
	
	if (status != toggle) 
	{
		if (status) 
		{
			counter++;
		}
	} 
	
	toggle = status;
	
	if (status) 
	{
		high(0);
		delayms(50);
		
	} 
	else
	{
		low(0);
		delayms(50);
	}
	
	if (counter % 2 == 0) {
		high(6);
		printf("Hello World!\n\r");
	} else {
		low(6);
	}
}

int putchar(int character) {
	while (!(UTCTL0 & TXEPT)) {}   // wait util tx buffer is free
	TXBUF0 = character;            // send character
	return 1;
}