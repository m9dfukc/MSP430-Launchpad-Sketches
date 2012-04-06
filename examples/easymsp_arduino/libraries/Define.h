// Define file

#define I2C 1
#define SPI 2
#define NONE 0

#define MSBFIRST 1
#define LSBFIRST 0

#define HIGH 1
#define LOW 0

#define FILTERON 1
#define FILTEROFF 0
#define YES 1
#define NO 0
#define EXTERN 9
#define DIODE 6
#define VDDHALF 7
#define VDDQUATER 8

#define M16 16
#define M12 12
#define M8 8
#define M1 1
#define K500 2
#define K400 17
#define K100 10
#define K12 15

#define DEFAULT 1
#define INTERNAL 2
#define INTERNAL1V5 3
#define INTERNAL2V56 4
#define EXTERNAL 5

#define FAST 1
#define SLOW 0

#define ACLK 1
#define SMCLK 2
#define MCLK 3

#define FALLING_EDGE 1
#define RISING_EDGE 0

#define YES 1
#define NO 0

#define ON 1
#define OFF 0

#define BINARY 0
#define TWOCOMP 1

#define INVERTED 1
#define NOTINVERTED 0

#define KEY 0xBEEF

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
