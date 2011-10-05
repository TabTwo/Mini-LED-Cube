#	Mini-LED-Cube 1.0
#
#	Copyright (C) 2009 Paul Wilhelm <paul@mosfetkiller.de>
#	http://mosfetkiller.de/?s=miniledcube

# Project specific settings
TARGET = miniledcube-1.0
MCU = attiny2313
SRC = main.c

# You probably want to change this to your own programming device

# AVR ISP mkII
PGMDEV = dragon_isp
PGMOPT = -P usb	# Try   -B 10   in case of programming errors

# Pony-STK200
#PGMDEV = pony-stk200
#PGMOPT = -E noreset 

# AVR-GCC and AVRDUDE need to be installed
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
REMOVE = rm -f

# Some C flags
CSTANDARD = gnu99
CFLAGS = -Wall -O2

help:
	@echo
	@echo "Availiable targets:"
	@echo "    help - Display this help"
	@echo
	@echo "    compile - Compiles source code"
	@echo "    info - Outputs device memory information"
	@echo "    program - Programs the device"
	@echo "    clean - Deletes temporary files"
	@echo "    fuses - Writes fuse settings to device (necessary only once per device)"
	@echo
	@echo "    all - Compile, info, program, clean"
	@echo
	@echo "IMPORTANT: Device programming may only be possible as super user"
	@echo
	@echo "See Makefile for contact information."
	@echo

all: compile info program clean

compile:
	@$(CC) -std=$(CSTANDARD) $(CFLAGS) -mmcu=$(MCU) $(SRC) -o $(TARGET).elf
	@$(OBJCOPY) -O ihex -j .text -j .data $(TARGET).elf $(TARGET).hex

info:
	avr-size $(TARGET).elf

program:
	@$(AVRDUDE) -p $(MCU) -u -V -c $(PGMDEV) $(PGMOPT) -U flash:w:$(TARGET).hex:i

fuses:
	@$(AVRDUDE) -p $(MCU) -u -V -c $(PGMDEV) $(PGMOPT) -U lfuse:w:0xE4:m -U hfuse:w:0xDF:m

clean:
	@$(REMOVE) $(TARGET).elf

