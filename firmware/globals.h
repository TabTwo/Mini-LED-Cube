/*  CTHN.de MiniLEDCube
 *
 *  By Kai Lauterbach (klaute at web dot de) 11/2011
 *
 *  License: General Public License (GPL v3)
 *
 */

#define F_CPU 12000000UL

#define MODE_ANIMATION_STOP   0
#define MODE_ANIMATION_SINGLE 1
#define MODE_ANIMATION_LOOP   2

#define MAX_EEPROM_FRAMES 32

#ifndef EEMEM
#define EEMEM  __attribute__ ((section (".eeprom")))
#endif
