/*  CTHN.de MiniLEDCube
 *
 *  Kai Lauterbach (klaute at web dot de)
 *
 *  License: General Public License (GPL v3)
 *
 */

#define F_CPU 12000000UL

// Bitshifting
#define    set_bit(var, bit)    ((var) |= (1 << (bit)))
#define    clear_bit(var, bit)  ((var) &= (unsigned)~(1 << (bit)))

