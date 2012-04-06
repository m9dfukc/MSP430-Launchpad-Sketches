/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

//Flash Ops

static unsigned int flash_lock = 0;

static inline void flashLock(void);
static inline int flashUnlock(unsigned int key);
static inline int flashReadWord(unsigned int address);
static inline char flashReadByte(unsigned int address);
static int flashWriteWord(unsigned int address, unsigned int data);
static int flashEraseSegment(unsigned int key, unsigned int segment);
static int flashEraseMainMemory(unsigned int key);
static int flashEraseAll(unsigned int key);


static inline void flashLock(void)
{
	FCTL3 |= FWKEY + LOCK; //Lock the flash
}

static inline int flashUnlock(unsigned int key)
{
	if (key == KEY)
	{
		FCTL3 &= FWKEY + ~LOCK; //Key entered correctly, Unlock flash.
		return(1); //Return with success
	}
	else
	{
		return(-1); //Return with failure.
	}
}

static inline int flashReadWord(unsigned int address)
{
	unsigned int* address_ptr=0;
	*address_ptr = address;
	
	return(*address_ptr);
}

static inline char flashReadByte(unsigned int address)
{
	unsigned int* address_ptr=0;
	*address_ptr = address;
	
	return((*address_ptr) << 8);
}

static int flashWriteWord(unsigned int address, unsigned int data)
{	
	disableWD(); //Disable Watchdog if enabled.
	setFreq(M1); //Set MCLK to 1Mhz
	
	unsigned int* address_ptr=0;
	*address_ptr = address;
	
	FCTL2 |= FWKEY + FSSEL_1 + BIT1 + BIT0; //MCLK / 3 = Flash clock
	FCTL1 |= FWKEY + WRT; //Enable write
	flashUnlock(KEY); //Unlock Flash
	*address_ptr = data; //Write Data
	flashLock(); //Relock flash
	FCTL1 &= FWKEY + ~WRT; //Disable write
	
	if ((FCTL3 & FRKEY + FAIL) > 0) //Was the write a sucess
	{
		FCTL3 &= FWKEY + ~FAIL; //Clear fail flag
		return(-1); //No
	}
	else
	{
		return(1); //Yes
	}
}


static int flashEraseSegment(unsigned int key, unsigned int segment)
{
	if(key == KEY)
	{
		//Erase segment
		//To be added
		return(1);
	}
	else
	{
		return(-1);
	}
}

static int flashEraseMainMemory(unsigned int key)
{
	if (key != KEY)
	{
		return(-1);
	}
	else
	{
	//To be added
		return(1); //Success
	}
}

static int flashEraseAll(unsigned int key)
{	
	if (key != KEY)
	{
		return(-1);
	}
	else
	{
	//To be added
		return(1); //Success
	}
}
