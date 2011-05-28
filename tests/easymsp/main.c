/* LED p1.0 & p1.6 toggle example */

#include "libraries/easymsp.h"

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
	} else {
		low(6);
	}
}