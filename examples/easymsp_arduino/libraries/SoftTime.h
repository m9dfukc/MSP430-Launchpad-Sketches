/*This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

//Copyright 2011:
//Matthew Burmeister

//delayus
//--------------------------------------------------------
//Delay execution by "x" microseconds.

static inline void delayus(register unsigned int time);
static inline void _us(void);
static inline void delayms(register unsigned int time);
static inline void delaysec(register unsigned int time);
static inline void delay(register unsigned int time);


static inline void delayus(register unsigned int time)
{
     while(time != 0)
     {
              _us();
              time--;
     }
}  

//_us
//Used for internal use only
static inline void _us(void)
{
	register int nop=1;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
	nop++;
}

//delayms
//--------------------------------------------------------
//Delay execution by "x" miliseconds

static inline void delayms(register unsigned int time)
{
	
	while (time != 0)
	{
          register unsigned int us = 34;
          
          while(us != 0)
          {
                   delayus(1);
                   us--;
          }
          
          time--;
     }
}


//delaysec
//--------------------------------------------------------
//Delay execution by "x" seconds.

static inline void delaysec(register unsigned int time)
{
	while(time != 0)
	{
		delayms(1000);
		time--;
	}
}

static inline void delay(register unsigned int time)
{
	delayms(time);
}
	
