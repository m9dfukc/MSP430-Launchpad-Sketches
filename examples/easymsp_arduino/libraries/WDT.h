/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Copyright 2011 Matthew Burmeister

//WDT+

static int enableTimer(unsigned int clocksource, unsigned int divs);
static void disableTimer(void);

static void clearWD(void);
static void disableWD(void);
static int enableWD(unsigned int clocksource, unsigned int divs);

#ifdef WDT_INT
extern void WDT_int(void);

#endif

static inline void clearWD(void)
{
	WDTCTL |= WDTPW + WDTCNTCL; //Clear the watchdog timer by setting WDTCNTCL.
}

static inline void disableWD(void)
{
	WDTCTL = WDTPW + WDTHOLD; //Disables the watchdog by setting the hold bit(WDTHOLD)
}

static inline void disableTimer(void)
{
	WDTCTL = WDTPW + WDTHOLD;
}

static int enableWD(unsigned int divider, unsigned int clocksource)
{
	unsigned int wdt=0;

	WDTCTL = WDTPW + 0;
	//wdt |= WDTPW + WDTHOLD;
	
	if (clocksource == ACLK)
	{
		wdt |= WDTPW + WDTSSEL;
	}
	
	switch (divider)
	{
		default:
			return(-1);
		break;
		
		case 64:
			clearWD();
			wdt |= WDTPW + BIT1 + BIT0;
		break;
		
		case 512:
			clearWD();
			wdt |= WDTPW + BIT1;
		break;
		
		case 8192:
			clearWD();
			wdt |= WDTPW + BIT0;
		break;
		
		case 32768:
			clearWD();
		break;
	}
	
	//wdt &= ~WDTHOLD;
	
	WDTCTL = wdt;
	
	return(1);
	
}

static int enableTimer(unsigned int clocksource, unsigned int divider)
{
	WDTCTL = WDTPW + 0; //Clear the watchdog timer.
	
	unsigned int wdt=0;
	
	//wdt |= WDTPW + WDTHOLD; //Set WDTHOLD to halt the watchdog timer.
	
	wdt |= WDTPW + WDTTMSEL; //Set WDTTMSEL to enable timer mode.
	
	if (clocksource == ACLK) //What clock did the user select?
	{
		wdt |= WDTPW + WDTSSEL; //Looks like ALCK, so set thw WDTSSEL bit.
	}
	
	switch (divider) //Lets do a switch to find the selected clock divider.
	{
		default:
			return(-1); //Whoops, user entered wrong settings, so lets abort.
		break;
		
		case 64:
			clearWD();
			wdt |= WDTPW + BIT1 + BIT0; 
		break;
		
		case 512:
			clearWD();
			wdt |= WDTPW + BIT1;
		break;
		
		case 8192:
			clearWD();
			wdt |= WDTPW + BIT0;
		break;
		
		case 32768:
			clearWD(); //Do nothing, As BIT0 and BIT1 are already clear
		break;
	}
	
	IE1 |= WDTIE; //Enable interrupts
	
	//wdt &= ~WDTHOLD; //Enable the timer
	
	WDTCTL = wdt; //Transfer settings
	
	//All of the config is done, We can return control to the user program
	
	return(1); //Return config success

}	
	
#ifdef WDT_INT
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	WDT_int();
}

#endif
