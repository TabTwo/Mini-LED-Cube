//  Mini-LED-Cube 1.0
//
//  Copyright (C) 2009 Paul Wilhelm <paul@mosfetkiller.de>
//  http://mosfetkiller.de/?s=miniledcube
//
//  Changed by Kai Lauterbach (klaute at web dot de)
//
//  Externes Quarz, CKDIV8 Disabled

#ifndef __main_h__
#define __main_h__

// Includes
#include "globals.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Cube-Data
//volatile uint32_t cube = 0x07007007; // Aktuelles Frame
volatile uint32_t cube = 0xffffffff; // Aktuelles Frame
//volatile uint32_t cube = 0x00000000; // Aktuelles Frame
// Bit Offset in Cube-Data
volatile uint8_t cube_level = 0; // Ebene

// Prototypen
void init(void);

extern void init_usb(void);
extern void usbPoll(void);

#endif // __main_h__

