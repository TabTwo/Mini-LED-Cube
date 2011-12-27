/*
 * CTHN.de MiniLEDCube
 *
 *  By Kai Lauterbach (klaute at web dot de) 11/2011
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
#include <avr/eeprom.h>

/*! \brief Cube-Data
 * bit  0 -  8 = level 1
 * bit  9 - 17 = level 2
 * bit 18 - 26 = level 3
 * bit 27 - 31 = The delay in ISR calls multiplied with 8 until
 *               the next frame will be shown (load from the EEPROM)
 */
uint32_t frame;

uint8_t level; // current layer
uint8_t mode = MODE_ANIMATION_LOOP; // firmware mode
uint8_t frmnum; // frame nummber in the animation loop
uint8_t delay; // delay in ISR calls between changing to the next animation frame

// eeprom array of the animation
uint32_t eep_anim[MAX_EEPROM_FRAMES] EEMEM;

// function prototypes
void init(void);

extern void init_usb(void);
extern void usbPoll(void);

#endif // __main_h__

