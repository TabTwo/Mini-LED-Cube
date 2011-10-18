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
//#include <util/delay.h>
//#include <avr/pgmspace.h>
//#include <avr/wdt.h>

// Cube-Array
uint8_t cube[3][3][3];
uint8_t buffer[3][3][3];    // Framebuffer

volatile uint8_t frame_done = 0;

// Prototypen
void init(void);
void loop(uint8_t);

extern void init_usb(void);
extern void usbPoll(void);

#endif // __main_h__

