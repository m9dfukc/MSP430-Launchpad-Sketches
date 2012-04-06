/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

static unsigned int compare(register unsigned int pin);
static void compareConfig(register unsigned int ref, register unsigned int _short, register unsigned unt filter);

static void compareConfig(register unsigned int ref, register unsigned int _short, register unsigned int filter)
{
	if (ref == DIODE)
		CACTL1 |= BIT4 + BIT5;
		
	if (ref == EXTERN)
		CACTL1 &= ~BIT4 + ~BIT5;
	
	if (ref == VDDHALF)
		CACTL1 |= BIT5;
		CACTL1 &= ~BIT4;
		
	if (ref == VDDQUATER)
		CACTL1 |= BIT4;
		CACTL1 &= ~BIT5;
		
	if (_short == YES)
		CACTL2 |= CASHORT;
		else
			CACTL2 &= ~CASHORT;
			
	if (filter == FILTERON)
		CACTL2 |= CAF;
		else
			CACTL2 &= ~CAF;
			
}

static unsigned int compare(register unsigned int pin)
{
	pin = pin << 3;
	CACTL2 |= pin;
	
	CACTL1 |= CAON;
	
	register unsigned int result=0;
	
	result = CACTL2 & CAOUT;
	if (result > 0)
	{
		CACTL1 &= ~CAON;
		return (0);
	}
	else
	{
		CACTL1 &= ~CAON;
		return (1);
	}
}
