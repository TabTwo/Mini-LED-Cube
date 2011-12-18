/*  CTHN.de MiniLEDCube
 *
 *  Kai Lauterbach (klaute at web dot de)
 *
 *  Based on http://mosfetkiller.de/?s=miniledcube
 *
 *  License: General Public License (GPL v3)
 *
 */

#include <avr/io.h>

typedef struct
{
    uint32_t frame: 27;
    uint32_t level:  2; // 00 01 10
    uint32_t mode:   3;
} cube_t;

