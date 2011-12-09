/*  CTHN.de MiniLEDCube
 *
 *  Kai Lauterbach (klaute at web dot de)
 *
 *  Based on http://mosfetkiller.de/?s=miniledcube
 *
 *  License: General Public License (GPL v3)
 *
 */

#ifndef __main_h__
#define __main_h__

// Includes
#include "globals.h"

#include <avr/interrupt.h>
#include <avr/io.h>

// Cube-Data
uint32_t cube = 0xffffffff;
// Bit Offset in Cube-Data
uint8_t cube_level; // = 0; // Ebene

// Prototypen
void init(void);

extern void init_usb(void);
extern void usbPoll(void);

#endif // __main_h__

