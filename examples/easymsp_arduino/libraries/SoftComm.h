/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Designed, Written and debugged by:
//Matthew Burmeister

//SoftComm

static void shiftOut(unsigned int DOUT, unsigned int SCLK, unsigned int bitorder, unsigned char data);
static char shiftIn(unsigned int DIN, unsigned int SCLK, unsigned int bitorder);

static char I2C_Device = 0;
static int I2C_SCL = 0;
static int I2C_SDA = 0;
static int I2C_CONFIG = NO;

static void shiftOut(unsigned int DOUT, unsigned int SCLK, unsigned int bitorder, unsigned char data)
{
	register unsigned char bits=8;
	register unsigned char value=0;
	
	while(bits != 0)
	{
		if (bitorder == MSBFIRST)
		{
			value = data & 0x80;
		}
		else
		{
			value = data & 0x01;
		}
		
		high(SCLK);
		
		if (value > 0)
		{
			high(DOUT);
		}
		else
		{
			low(DOUT);
		}
		
		low(SCLK);
		
		if (bitorder == MSBFIRST)
		{
			data = data << 1;
		}
		else
		{
			data = data >> 1;
		}
		
		bits--;
	}
}

static char shiftIn(unsigned int DIN, unsigned int SCLK, unsigned int bitorder)
{
	register unsigned int bit=0;
	register unsigned int clock=0;
	register unsigned char bits=8;
	register unsigned char data=0;
	register unsigned int bit_unvalid_time = 5000;
	
	while (bits != 0)
	{
		clock = read(SCLK);
		
		while (clock == 0)
		{
			if (bit_unvalid_time == 0)
			{
				return (0);
			}
			
			clock = read(SCLK);
			
			bit_unvalid_time--;
		}
		
		bit = read(DIN);
		
		if (bit > 0)
		{
			if (bitorder == MSBFIRST)
			{
				data |= 0x80;
			}
			else
			{
				data |= 0x01;
			}
		}
		else
		{
			if (bitorder == MSBFIRST)
			{
				data |= 0x80;
			}
			else
			{
				data |= 0x01;
			}
		}
		
		if (bitorder == MSBFIRST)
		{
			data = data >> 1;
		}
		else
		{
			data = data << 1;
		}
		
		bits--;
		
		clock = read(SCLK);
		
		while(clock > 0)
		{
			
			if (bit_unvalid_time == 0)
			{
				return (0);
			}
			
			clock = read(SCLK);
			
			bit_unvalid_time--;
		}
		
	}
	
	return (data);
}

static void i2cConfig(unsigned int SDA, unsigned int SCL, unsigned int device)
{
	I2C_Device = device;
	I2C_SDA = SDA;
	I2C_SCL = SCL;
	I2C_CONFIG = YES;
	high(SDA);
	high(SCL);

}

static int i2cOut(unsigned char data)
{
	if (I2C_CONFIG == NO)
	{
		return(-2);
	}
	
	low(I2C_SDA); //Generate START
	low(I2C_SDA);
	
	unsigned char bits = 8;
	unsigned char daddress = I2C_Device;
	
	daddress = daddress << 1;
	
	while (bits != 0) //Transmit Address
	{
		delayus(400);
		
		low(I2C_SCL);
		
		unsigned char address = daddress & 0x80;
		
		if (address> 0)
		{
			high(I2C_SDA);
		}
		else
		{
			low(I2C_SDA);
		}
		
		daddress = daddress << 1;
		bits--;
		
		delayus(400);
		
		high(I2C_SCL);
	}
	
	
	unsigned invalid = 200;
	unsigned int result;
	while(invalid != 0) //Wait for ACK
	{
		result = read(I2C_SCL);
		
		if (result == 0)
		{
			invalid = 0;
		}
		
		invalid--;
	}
	low(I2C_SCL);
	delayus(400);
	high(I2C_SCL);
	delayus(400);
	
	result = read(I2C_SDA);
	
	if (result = 0)
	{
		return(-1); //No device
	}
	
	bits = 8;
	
	while (bits != 0) //Transmit data
	{
		delayus(400);
		low(I2C_SCL);
		
		unsigned char datatosend = data & 0x80;
		
		if (datatosend > 0)
		{
			high(I2C_SDA);
		}
		else
		{
			low(I2C_SDA);
		}
		
		datatosend = datatosend << 1;
		bits--;
		
		delayus(400);
		
		high(I2C_SCL);
	}
	
	
	high(I2C_SDA);
	high(I2C_SCL);
	
	return(1);
}
	
