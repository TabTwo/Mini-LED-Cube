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
extern int lc_saveFrame(unsigned long, int, int);
extern void lc_init(void);
extern void lc_close(void);

int main(int argc, char **argv)
{

    lc_init();


    //lc_close();

    //return 0;
    if (argc == 2 && !strcmp((char*)argv[1], "--stop"))
    {
        printf("stop animation loop\n");
        lc_setMode(MODE_ANIMATION_STOP);
    }
    else if (argc == 2 && !strcmp((char*)argv[1], "--loop"))
    {
        printf("starting animation loop\n");
        lc_setMode(MODE_ANIMATION_LOOP);
    }
    else if (argc == 5 && !strcmp((char*)argv[1], "--save"))
    {

        lc_setMode(MODE_ANIMATION_STOP);

        /*printf(">>> %s <<<\n", argv[1]);
        printf(">>> %s <<<\n", argv[2]);
        printf(">>> %s <<<\n", argv[3]);*/
        // TODO parse commandline parameters
        unsigned int pos = 0;
        if ( sscanf((char*)argv[2], "%d", &pos) )
        {
            unsigned int delay = 0;
            if ( sscanf((char*)argv[3], "%d", &delay) )
            {
                unsigned int frame = 0;
                if ( sscanf((char*)argv[4], "0x%08x", &frame) )
                {
                    printf("saving frame: index=%d delay=%d frame=0x%08x\n", pos, delay, frame);
                    //lc_setFrame(frame);
                    lc_saveFrame(frame, delay, pos);
                }
            }
        }

    }

    lc_close();

    return 0;
}

