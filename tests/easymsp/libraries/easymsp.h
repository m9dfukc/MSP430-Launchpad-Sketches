/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

#ifndef EASYMSP081_H
#define EASYMSP081_H

//#include <msp430.h>

/* oder vielleicht: 
 #include <math.h>
 
 #include <stdint.h>
 #include <io.h>
 #include <signal.h>
*/

#include <msp430x22x2.h>



//Macro functions
//-------------------------------------------------------------------------------------------------------------------
#define constrain(x, min, max)   if(x > max) { x = max; } else if(x < min) { x = min; }
#define map(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#define min(x, max_value)  if((x) > max_value) { (x) = max_value; }
#define max(x, min_value)  if((x) < min_value) { (x) = min_value; }
#define bit(n)             (1 << n)
#define bitClear(x, n)     x &= ~bit(1)
#define bitSet(x, n)       x |= bit(1)
#define bitRead(x, n)      ((x & bit(1)) >> n)
#define bitWrite(x, n, b)  if(!b) { bitClear(x, n); } else { bitSet(x, n); }
#define lowByte(x)         ((unsigned char)(x & 0xFF))
#define highByte(x)        ((unsigned char)(x >> 8))
//-----------------------------------------------------------------------------------------------------------------------


//References for ADC and Compare
//------------------------------------------------------------------------------------------------

static const unsigned int DEFAULT = 1;
static const unsigned int INTERNAL = 2;
static const unsigned int INTERNAL1V1 = 3;
static const unsigned int INTERNAL2V56 = 4;
static const unsigned int EXTERNAL = 5;

static const unsigned int DIODE = 6;
static const unsigned int VDDHALF = 7;
static const unsigned int VDDQUATER = 8;

//-------------------------------------------------------------------------------------------------

//Compare Settings
//-------------------------------------------------------------------------------------------------
static const unsigned int FILTERON = 1;
static const unsigned int FILTEROFF = 0;
static const unsigned int YES = 1;
static const unsigned int NO = 0;
//-------------------------------------------------------------------------------------------------

//Clock modes
//-------------------------------------------------------------------------------------------------
static const unsigned int M16 = 16;
static const unsigned int M12= 12;
static const unsigned int M8 = 8;
static const unsigned int M1 = 1;
static const unsigned int K500 = 2;
static const unsigned int K100 = 10;
static const unsigned int K12 = 15;

static unsigned int currentclock = 1; //This varible holds the system current clock.
//--------------------------------------------------------------------------------------------------

//Buffers
//-------------------------------------------------------------------------------------------------
static unsigned int uartBuffer[16];
static unsigned char uartIndex=0;

//==========================================================================
//Start functions
//==========================================================================

//delayus
//--------------------------------------------------------
//Delay execution by "x" microseconds.

static void delayus(register unsigned int time)
{
	register unsigned int timeus;
	
	while (time > 0)
	{
		timeus=16 * currentclock;
		
		while (timeus > 0)
		{
			timeus--;
		}
		
		time--;
	}
}

//delayms
//--------------------------------------------------------
//Delay execution by "x" miliseconds

static void delayms(register unsigned int time)
{
	while(time !=0)
	{
		delayus(10);
		time--;
	}
}

//delaysec
//--------------------------------------------------------
//Delay execution by "x" seconds.

static void delaysec(register unsigned int time)
{
	while(time != 0)
	{
		delayms(10);
		time--;
	}
}
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


//High
//---------------------------------------------------------
static void high(register unsigned int pin)
{
	if (pin <= 7)
	{
		pin = bit(pin);
		
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
	
	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
		P3OUT |= pin;
	}
}


//Low
//----------------------------------------------------
static void low(register unsigned int pin)
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
	
	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
		P3OUT &= ~pin;
	}
}

//output
//----------------------------------------------------------------------------

static void output(register unsigned int pin)
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
	
	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR |= pin;
	}
}

//input
//--------------------------------------------------------------------------------------

static void input(register unsigned int pin)
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
	
	if (pin <= 32 && pin >= 17)
	{
		pin = pin - 16;
		pin = bit(pin);
		
		P3DIR &= ~pin;
	}
}

//Read
//---------------------------------------------------------------

static unsigned int read(register unsigned int pin)
{
	if (pin <= 7){
		return (P1IN & bit(pin));}
		
	if (pin <= 16 && pin >= 8){
		return (P2IN & bit(pin));}
		
	if (pin <= 32 && pin >= 17){
		return (P3IN & bit(pin));}
		
	return(0);
}

static unsigned int analogRead(register unsigned int pin)
{
	//Ok, we need to setup the ADC10.
	//ADC10CTL0 |= SREF_0; //Set Ref to VCC and VDD
	ADC10CTL0 |= ADC10SHT_0; //Sample And Hold 4 clokcs
	//ADC10CTL0 |= ADC10SR; // enable for low power mode
	//ADC10CTL0 |= REFBURST;
	switch(pin)
	{
		case 0x01:
		ADC10CTL1 |= INCH_0;
		ADC10AE0 |= 0x01;
		break;
		
		case 0x02:
		ADC10CTL1 |= INCH_1;
		ADC10AE0 |= 0x02;
		break;
		
		case 0x04:
		ADC10CTL1 |= INCH_2;
		ADC10AE0 |= 0x04;
		break;
		
		case 0x08:
		ADC10CTL1 |= INCH_3;
		ADC10AE0 |= 0x08;
		break;
		
		case 0x010:
		ADC10CTL1 |= INCH_4;
		ADC10AE0 |= 0x10;
		break;
		
		case 0x20:
		ADC10CTL1 |= INCH_5;
		ADC10AE0 |= 0x20;
		break;
		
		case 0x40:
		ADC10CTL1 |= INCH_6;
		ADC10AE0 |= 0x40;
		break;
		
		case 0x80:
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
	
	int ADCBUSY=0;
	
	while (ADCBUSY != 1)
	{
		ADCBUSY = ADC10CTL1 & ADC10BUSY;
	}
	
	return (ADC10MEM);
	
}


static void analogReference(register unsigned int ref)
{
	if (ref == DEFAULT)
	{
		ADC10CTL0 &= ~SREF_7; //Clear the register
		ADC10CTL0 |= SREF_0;
	}
	
	if (ref == INTERNAL)
	{
		ADC10CTL0 &= ~SREF_7; //Clear the register
		ADC10CTL0 |= SREF_0;
	}
	
	if (ref == INTERNAL1V1)
	{
		ADC10CTL0 &= ~SREF_7; //Clear the register
		ADC10CTL0 |= SREF_1 + REFON;
		ADC10CTL0 &= ~REF2_5V;
	}
	
	if (ref == INTERNAL2V56)
	{
		ADC10CTL0 &= ~SREF_7; //Clear the register
		ADC10CTL0 |= SREF_1 + REFON + REF2_5V;
	}
	
	if (ref == EXTERNAL)
	{
		ADC10CTL0 &= ~SREF_7; //Clear the register
		ADC10CTL0 |= SREF_2;
	}
}


static inline void shutdown()
{
	//Enters the CPU into LPM4
  __bic_SR_register(CPUOFF + OSCOFF + SCG0 + SCG1);
}


static void setFreq(register unsigned int FREQ)
{
		//BCSCTL2 = 0;
		//BCSCTL1 = 0;
		
		if (FREQ == M16)
		{
		//Set CPU to 16MHZ
		currentclock = M16;
		BCSCTL1 = CALBC1_16MHZ;
		DCOCTL = CALDCO_16MHZ;

		}
		
		if (FREQ == M12)
		{
		//Set CPU to 12Mhz
		currentclock = M12;
		BCSCTL1 = CALBC1_12MHZ;
		DCOCTL = CALDCO_12MHZ;

		}
		
		if (FREQ == M8)
		{
		//Set CPU to 4Mhz
		currentclock = M8;
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;

		}
		
		if (FREQ == M1)
		{
		//Set CPU to 1MHZ
		currentclock = M1;
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
		}	
			
		if (FREQ == K500)
		{
				currentclock = K500;
				BCSCTL1 = CALBC1_1MHZ;
				BCSCTL2 = DIVM_1 + DIVS_1;
				DCOCTL = CALDCO_1MHZ;
				
		}
		
		if (FREQ == K100)
		{
		//Set CPU to 100KHZ
		currentclock = K100;
		BCSCTL1 = CALBC1_1MHZ;
		BCSCTL2 = DIVM_1 + DIVS_3;
		DCOCTL = CALDCO_1MHZ;
		
		
		}
		
		if (FREQ == K12)
		{
		//Set CPU to 12Khz
		BCSCTL2 |= BIT7 + BIT6;
		}
}

static void compareConfig(register unsigned int ref, register unsigned int _short, register unsigned int filter)
{
	if (ref == DIODE)
		CACTL1 |= BIT4 + BIT5;
		
	if (ref == EXTERNAL)
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

static unsigned int compare(register unsigned int pin1)
{
	pin1 = pin1 << 3;
	CACTL2 |= pin1;
	
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

#endif /*EASYMSP081_*/
