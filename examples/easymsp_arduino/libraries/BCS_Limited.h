/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

//Limited Range BCS+

static void setFreq(unsigned int FREQ);

//-------------------------------------------------------------------------------------------------

static unsigned int currentclock = 1; //This varible holds the system current clock.

static void setFreq(unsigned int FREQ)
{
	//BCSCTL2 = 0;
	//BCSCTL1 = 0;
		
		
	if (FREQ == M1)
	{
		//Set CPU to 1MHZ
		DCOCTL = 0;
		currentclock = M1;	
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
	}	
		
	if (FREQ == K500)
	{
		DCOCTL = 0;
		currentclock = K500;
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
