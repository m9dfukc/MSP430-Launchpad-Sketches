//Arduino sub system

extern void high(unsigned int pin);
extern void low(unsigned int pin);
extern unsigned int read(unsigned int pin);
extern inline void delay(register unsigned int time);
extern inline void delayms(unsigned int time);
extern inline void delaysec(unsigned int time);
extern inline void delayus(unsigned int time);
extern void setup();
extern void loop();
extern inline void stopwd();

static void digitalWrite(unsigned int pin, unsigned int state)
{
	if(state == HIGH)
	{
		high(pin);
	}
	else
	{
		low(pin);
	}
}

static unsigned int digitalRead(unsigned int pin)
{
	register unsigned int val = read(pin);
	return(val);
}

static void delayMicroseconds(unsigned int time)
{
	delayus(time);
}

static void micros(unsigned int time)
{
	delayus(time);
}

static void millis(unsigned int time)
{
	delayms(time);
}