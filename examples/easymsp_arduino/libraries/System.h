/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Copyright 2011 Matthew Burmeister

#include <stdint.h>
#include "Define.h"

#ifndef ARDUINO

static inline void setup();

#else

extern void setup();
extern void loop();

#endif

static int _lowpower = 0;

static inline void stopwd();
static inline void reset();
static inline void shutdown();
static void sleep(unsigned int time, unsigned int mode);
static inline void lowPowerModeOn(void);
static inline void lowPowerModeOff(void);

//==========================================================================
//Start functions
//==========================================================================

#ifndef ARDUINO

static inline void setup()
{
	stopwd();
}	

#else

int main()
{
	stopwd();
	setup();
	
	while(1)
	{
		loop();
	}
	
	return 1;
}

#endif

//Reset
//-------------------------------------------------------
//Reset the microcontroller

static inline void reset(void)
{
	WDTCTL = 0;
}

//StopWD
//--------------------------------------------------------
//Stop the Watchdog from reseting the system.

static inline void stopwd(void)
{
	WDTCTL = WDTPW + WDTHOLD;
}


static inline void shutdown(void)
{
	//Enters the CPU into LPM4
  __bic_SR_register(CPUOFF + OSCOFF + SCG0 + SCG1);
}

static void sleep(unsigned int time, unsigned int mode)
{
	//To be added
}

static inline void lowPowerModeOn(void)
{
	_lowpower = 1;
}

static inline void lowPowerModeOff(void)
{
	_lowpower = 0;
}

