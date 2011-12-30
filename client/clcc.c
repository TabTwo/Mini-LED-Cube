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

#include "globals.h"

#include "../firmware/globals.h"

// External functions to control the ledcube.
extern void lc_setFrame(unsigned long);
extern void lc_setMode(int);
extern void lc_saveFrame(unsigned long, int);
extern void lc_init(void);
extern void lc_close(void);

int main(int argc, char **argv)
{

    lc_init();

    lc_setMode(MODE_ANIMATION_STOP);

    // TODO parse commandline parameters
    unsigned int frame = 0;
    if ( sscanf((char*)argv[1], "0x%08x", &frame) )
    {
        printf("0x%08x\n", frame);
        lc_setFrame(frame);
    }

    //lc_setMode(MODE_ANIMATION_LOOP);
    lc_close();

    return 0;
}

