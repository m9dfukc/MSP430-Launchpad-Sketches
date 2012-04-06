/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Copyright 2011 Matthew Burmeister
//ADC

static unsigned int analogRead(unsigned int pin);
static void analogReference(unsigned int ref);
static int analogConfig(unsigned int holdtime, unsigned int format, unsigned int invert);

static int _holdconfig = 0;

static unsigned int analogRead(unsigned int pin)
{
	//Ok, we need to setup the ADC10.
	if (_holdconfig == NO)
	{
	ADC10CTL0 |= ADC10SHT_0; //Sample And Hold 4 clokcs
	}
	
	if (_lowpower == ON)
	{
		ADC10CTL0 |= ADC10SR; // enable for low power mode
	}
	else
	{
		ADC10CTL0 &= ~ADC10SR;	
	}
	
	switch(pin)
	{
		case 0:
		ADC10CTL1 |= INCH_0;
		ADC10AE0 |= 0x01;
		break;
		
		case 1:
		ADC10CTL1 |= INCH_1;
		ADC10AE0 |= 0x02;
		break;
		
		case 2:
		ADC10CTL1 |= INCH_2;
		ADC10AE0 |= 0x04;
		break;
		
		case 3:
		ADC10CTL1 |= INCH_3;
		ADC10AE0 |= 0x08;
		break;
		
		case 4:
		ADC10CTL1 |= INCH_4;
		ADC10AE0 |= 0x10;
		break;
		
		case 5:
		ADC10CTL1 |= INCH_5;
		ADC10AE0 |= 0x20;
		break;
		
		case 6:
		ADC10CTL1 |= INCH_6;
		ADC10AE0 |= 0x40;
		break;
		
		case 7:
		ADC10CTL1 |= INCH_7;
		ADC10AE0 |= 0x80;
		break;
		
		case 0xFF:
		ADC10CTL1 |= INCH_10;
		break;
	}
	
	//ADC10CTL1 |= ISSH;
	ADC10CTL0 |= ADC10ON + ENC;
	ADC10CTL0 |= ADC10SC;
	
	while ((ADC10CTL1 & ADC10BUSY) != 1)
	{
	}
	
	return (ADC10MEM);
	
}


static void analogReference(unsigned int ref)
{
	switch (ref)
	{
		
		default:
			
		break;
		
		case DEFAULT:

			ADC10CTL0 &= ~SREF_7; //Clear the register
			ADC10CTL0 |= SREF_0;
		break;
	
	
		case INTERNAL:
	
			ADC10CTL0 &= ~SREF_7; //Clear the register
			ADC10CTL0 |= SREF_0;
		break;
	
		case INTERNAL1V5:
	
			ADC10CTL0 &= ~SREF_7; //Clear the register
			ADC10CTL0 |= SREF_1 + REFON;
			ADC10CTL0 &= ~REF2_5V;
		break;
	
		case INTERNAL2V56:
	
			ADC10CTL0 &= ~SREF_7; //Clear the register
			ADC10CTL0 |= SREF_1 + REFON + REF2_5V;
		break;
	
		case EXTERNAL:
		
			ADC10CTL0 &= ~SREF_7; //Clear the register
			ADC10CTL0 |= SREF_2;
		break;
		
	}
}

static int analogConfig(unsigned int holdtime, unsigned int format, unsigned int invert)
{
	switch (holdtime)
	{
		default:
			return(-1);
		break;
			
		case 4:
			ADC10CTL0 |= ADC10SHT_0; //4 Clocks
			_holdconfig = YES;
		break;
		
		case 8:
			ADC10CTL0 |= ADC10SHT_1; //8 clocks
			_holdconfig = YES;
		break;
		
		case 16:
			ADC10CTL0 |= ADC10SHT_2; //16 Clocks
			_holdconfig = YES;
		break;
		
		case 64:
			ADC10CTL0 |= ADC10SHT_3; //64 Clocks
			_holdconfig = YES;
		break;
	}
	
	switch (format)
	{
		default:
			return(-3);
		break;
		
		case BINARY:
		ADC10CTL1 &= ~ADC10DF;
		break;
		
		case TWOCOMP:
		ADC10CTL1 |= ADC10DF;
		break;
	}
	
	switch (invert)
	{
		default:
			return(-4);
		break;
		
		case INVERTED:
		ADC10CTL1 |= ISSH;
		break;
		
		case NOTINVERTED:
		ADC10CTL1 &= ~ISSH;
		break;
	}
	
	return(1);
}
