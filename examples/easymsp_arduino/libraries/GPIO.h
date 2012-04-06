/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

static void high(unsigned int pin);
static void low(unsigned int pin);
static void input(unsigned int pin);
static void output(unsigned int pin);
static unsigned int read(unsigned int pin);

//High
//---------------------------------------------------------
static void high(unsigned int pin)
{
	if (pin <= 7)
	{
		if (pin == 0)
		{
			pin = 0x01;
		}
		else
		{
			
			pin = bit(pin);
		}
		
			
		P1DIR |= pin;
		P1OUT |= pin;
	}
	
	if (pin <= 16 && pin >= 8)
	{
		pin = pin - 8;
		pin = bit(pin);
		
		P2DIR |= pin;
		P2OUT |= pin;
	}

#ifdef HASPORT3

	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
		P3OUT |= pin;
	}

#endif

}


//Low
//----------------------------------------------------
static void low(unsigned int pin)
{
	if (pin <= 7)
	{
		pin = bit(pin);
		
		P1DIR |= pin;
		P1OUT &= ~pin;
	}
	
	if (pin <= 16 && pin >= 8)
	{
		pin = pin - 8;
		pin = bit(pin);
		
		P2DIR |= pin;
		P2OUT &= ~pin;
	}
	
#ifdef HASPORT3

	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
		P3OUT &= ~pin;
	}

#endif

}

//output
//----------------------------------------------------------------------------

static void output(unsigned int pin)
{
	if (pin <= 7)
	{
		pin = bit(pin);
		
		P1DIR |= pin;
	}
	
	if (pin <= 16 && pin >= 8)
	{
		pin = pin - 8;
		pin = bit(pin);
		
		P2DIR |= pin;
	}
	
#ifdef HASPORT3

	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
	}

#endif

}

//input
//--------------------------------------------------------------------------------------

static void input(unsigned int pin)
{
	if (pin <= 7)
	{
		pin = bit(pin);
		
		P1DIR &= ~pin;
	}
	
	if (pin <= 16 && pin >= 8)
	{
		pin = pin - 8;
		pin = bit(pin);
		
		P2DIR &= ~pin;
	}
	
#ifdef HASPORT3

	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR &= ~pin;
	}

#endif

}

//Read
//---------------------------------------------------------------

static unsigned int read(unsigned int pin)
{
	if (pin <= 7)
	{
		if (P1IN & bit(pin) > 0)
		{
			return(0);
		}
		else
		{
			return(1);
		}
	}
		
	if (pin <= 16 && pin >= 8)
	{
	
		if(P2IN & bit(pin) > 0)
		{
			return(0);
		}
		else
		{
			return(1);
		}
		
	}
	
#ifdef HASPORT3
	
	if (pin <= 32 && pin >= 17)
	{
		if(P3IN & bit(pin) > 0);
		{
			return(0);
		}
		else
		{
			return(1);
		}
	}
		
#endif

	return(0);
}

