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

//#include "type.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

// Cube-Data
uint32_t frame = 0xffffffff;
// Bit Offset in Cube-Data
uint8_t level; // Aktive Ebene
uint8_t mode;
uint8_t frmnum;
uint8_t delay;
uint8_t delay_max;

//cube_t *cube;
uint32_t eep_anim[32] EEMEM;

// Prototypen
void init(void);

extern void init_usb(void);
extern void usbPoll(void);

void loadEEPROMFrame(uint8_t);

#endif // __main_h__

