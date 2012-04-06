/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

//Full Range BCS+


//-------------------------------------------------------------------------------------------------

static void setFreq(register unsigned it FREQ);

static unsigned int currentclock = 1; //This varible holds the system current clock.

static void setFreq(register unsigned int FREQ)
{
	//BCSCTL2 = 0;
	//BCSCTL1 = 0;
		
	if (FREQ == M16)
	{
		//Set CPU to 16MHZ
		currentclock = M16;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_16MHZ;
		DCOCTL = CALDCO_16MHZ;

	}
		
		if (FREQ == M12)
	{
		//Set CPU to 12Mhz
		currentclock = M12;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_12MHZ;
		DCOCTL = CALDCO_12MHZ;

	}
		
	if (FREQ == M8)
	{
		//Set CPU to 8Mhz
		currentclock = M8;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;

	}
		
	if (FREQ == M1)
	{
		//Set CPU to 1MHZ
		currentclock = M1;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
	}	
		
	if (FREQ == K500)
	{
		currentclock = K500;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_1MHZ;
		BCSCTL2 = DIVM_1 + DIVS_1;
		DCOCTL = CALDCO_1MHZ;
	
	}
		
	if (FREQ == K100)
	{
		//Set CPU to around 100KHZ
		currentclock = K100;
		DCOCTL = 0;
		BCSCTL1 = CALBC1_1MHZ;
		BCSCTL2 = DIVM_1 + DIVS_3;
		DCOCTL = CALDCO_1MHZ;
	
		
	}
		
	if (FREQ == K12)
	{
		//Set CPU to 12Khz
	}
}
