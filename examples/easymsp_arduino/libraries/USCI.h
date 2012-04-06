/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

//USCI

static void hspiConfig(int bitorder, int clockphase, int clockpol);
static void hspiOut(char data);
static char hspiIn(void);

static void hspiConfig(int bitorder, int clockphase, int clockpol)
{
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_2;
	
	if (bitorder == MSBFIRST)
	{
		UCA0CTL0 |= UCMSB;
	}
	else
	{
		UCA0CTL0 &= ~UCMSB;
	}
	
	if (clockpol == HIGH)
	{
		UCA0CTL0 |= UCCKPL;
	}
	else
	{
		UCA0CTL0 &= ~UCCKPL;
	}
	
	if (clockphase == 1)
	{
		UCA0CTL0 |= UCCKPH;
	}
	else
	{	
		UCA0CTL0 &= ~UCCKPH;
	}
	
	UCA0CTL0 |= UC7BIT + UCMST + UCMODE_0; //Took out USYNC
	
	UCA0CTL1 &= ~UCSWRST; //Clear the reset
}

static void hspiOut(char data)
{
	unsigned int status = UCA0STAT & UCBUSY;
	
	while(status > 0)
	{
		status = UCA0STAT & UCBUSY;
	}
	
	UCA0TXBUF = data;
}

static char hspiIn(void)
{
	unsigned int status = UCA0STAT & UCBUSY;
	
	while(status > 0)
	{
		status = UCA0STAT & UCBUSY;
	}
	
	return(UCA0RXBUF);
}