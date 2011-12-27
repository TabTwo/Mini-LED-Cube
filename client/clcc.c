/*
 * CTHN.de MiniLEDCube
 *
 *  By Kai Lauterbach (klaute at web dot de) 12/2011
 *
 *  Based on http://mosfetkiller.de/?s=miniledcube
 *
 *  License: General Public License (GPL v3)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <usb.h>
#include <argtable2.h>

#include "../firmware/globals.h"   /* custom request numbers */

// External functions to control the ledcube.
extern void lc_setFrame(unsigned long);
extern void lc_setMode(int);
extern void lc_saveFrame(unsigned long, int);
extern void lc_init(void);
extern void lc_close(void);

int main(int argc, char **argv)
{

    lc_init();

    // TODO parse commandline parameters

    lc_close();

    return 0;
}

