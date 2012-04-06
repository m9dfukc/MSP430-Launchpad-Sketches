/*
	EasyMSP Library includes files
*/

//Include device defs

#include <math.h>
#include <stdint.h>
#include <io.h>
#include <signal.h>

#include "System.h"
#include "GPIO.h"
#include "SoftTime.h"
#include "SoftComm.h"
#include "WDT.h"

#ifdef COREONLY

#else

//Device dependant features

#ifdef MSP430G2231

	#define supported
	
	#include "ADC10.h"
	#include "BCS_Limited.h"
	#include "USI.h"
	
#endif


#ifdef MSP430G2131

	#define supported
	
	#include "ADC10.h"

	#include "BCS_Limited.h"
	#include "USI.h"
	
#endif


#ifdef MSP430G2211
	
	#define supported
	
	#include "Comp.h"
	#include "BCS_Limited"
	
#endif


#ifdef MSP430G2553

	#define supported
	
	#define HASPORT3
	#define HASTWOTIMERS
	
	#include "USCI.h"
	#include "Comp.h"
	#include "ADC10.h"
	#include "BCS_Full"

#endif


#ifdef MSP430F2012

	#define supported


	#include "ADC10.h"
	#include "BCS_Full.h"
	#include "USI.h"
	
#endif

#include "Flash.h"

//Do we become a Arduino?

#ifdef ARDUINO
	
	#include "Arduino.h"
	
#endif


#ifdef Arduino
	
	#define ARDUINO
	
	#include "Arduino.h"
	
#endif


#ifdef arduino

	#define ARDUINO
	
	#include "Arduino.h"
	
#endif

#endif

//Check if the defined device is supported

#ifndef supported
	
	//#error "Device not supported or wrong device name" //Whoops, looks like someone herp derped.
	
#endif
