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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <usb.h>

#include "globals.h"

#include "../firmware/globals.h"

extern int lc_setFrame(unsigned long);
extern int lc_setMode(int);
extern int lc_saveFrame(unsigned long, int, int);
extern int lc_init(void);
extern int lc_close(void);

/*
 *
 */
void eeprom1()
{

    // lc_set animation stop
    lc_setMode(MODE_ANIMATION_STOP);


    int buf = 0;
    int tmp = 0;
    int tmp2 = 26;
    for (tmp = 0; tmp < 32; tmp++)
    {
        if (tmp < 27)
            buf = (1 << tmp);
        else
        {
            tmp2--;
            buf = (1 << tmp2);
        }

        printf("delay: %d pos: %d frame: 0x%08x\n", tmp, tmp, buf);
        // save to position tmp
        lc_saveFrame(buf, tmp, tmp);
        usleep(2500);

    }
    //
    // lc_set mode to animate endless loop
    lc_setMode(MODE_ANIMATION_LOOP);

}

/*
 *
 */
void sinus1(int max)
{

    // lc_set animation stop
    lc_setMode(MODE_ANIMATION_STOP);

    int j = max;
    while (--j)
    {

        int i = 0;
        int k = 0;
        //for (i = 0; i < 360; i+=11)
        for (i = 0; i < 360; i++)
        {
            // 2 = 27
            // 1 = 27 / 2
            // n = 27 * n / 2
            double d = cos((double)((6.28*i)/360)) + 1; // 6.28 = PI * 2
            unsigned long tmp = (1 << (int)((27 * d) / 2));

            // show frame
            lc_setFrame(tmp);
            // or save the frame to eeprom
            //tmp = tmp + (k << 27);
            //if (k < 32)
                //lc_saveFrame(tmp, k, k);

            usleep(2500);
            k++;
        }

    }

}

/*
 *
 */
void demo()
{
    // stop animation
    lc_setMode(MODE_ANIMATION_STOP);

    //clear cube
    lc_setFrame(0);

    sleep(1);

    // transfer one frame
    lc_setFrame(0x06127348);

    sleep(1);

    // another frame
    lc_setFrame(0x07007007);

    sleep(1);

    // switch all led on
    lc_setFrame(0x07ffffff);

    sleep(1);

    // save animation to eeprom and animate for 60 seconds
    eeprom1();

    sleep(10);

    // animate with a sinus wave
    sinus1(25);

    // start animation one time
    lc_setMode(MODE_ANIMATION_SINGLE);
}

int main(int argc, char **argv)
{

    if (lc_init() != SUCCESSFULLY_CONNECTED)
    {
        return -1;
    }

    demo();

    lc_setMode(MODE_ANIMATION_LOOP);

    lc_close();

    return 0;
}

