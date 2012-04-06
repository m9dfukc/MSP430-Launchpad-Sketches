MSP430_DIR		= /usr/local/msp430-toolchain/bin
MSPDEBUG_DIR	= /usr/local/bin


PROG			= main
CC				= $(MSP430_DIR)/msp430-gcc
CXX				= $(MSP430_DIR)/msp430-g++
OBJDUMP			= $(MSP430_DIR)/msp430-objdump
SIZE			= $(MSP430_DIR)/msp430-size
MSPDEBUG		= $(MSPDEBUG_DIR)/mspdebug
CFLAGS			= -Os -std=gnu99 -Wall -g -mmcu=msp430x2012

OBJS=$(PROG).o

all: $(PROG).elf $(PROG).lst
	$(SIZE) $(PROG).elf

.PHONY: all

$(PROG).elf: $(OBJS)
	$(CXX) $(CFLAGS) -o $(PROG).elf $(OBJS)

%.o: %.c
	$(CXX) $(CFLAGS) -c $<

%.lst: %.elf
	$(OBJDUMP) -DS $< >$@

clean:
	rm -fr $(PROG).elf $(PROG).lst $(OBJS)

install: $(PROG).elf
	$(MSPDEBUG) rf2500 "prog $(PROG).elf"
