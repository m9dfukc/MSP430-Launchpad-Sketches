//ADC12 Advanced Driver
static int _holdtime = 0;
static int _reference = 0;
static int _invert = 0;

static void analogConfig(unsigned int holdtime, unsigned int reference, unsigned int invert)
{
	switch (holdtime)
	{
		default:
			return(-1);
		break;
		
		