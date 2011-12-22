/* Name: lc_set-led.c
 * Project: hid-custom-rq example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-10
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: lc_set-led.c 692 2008-11-07 15:07:40Z cs $
 */

/*
General Description:
This is the host-side driver for the custom-class example device. It searches
the USB for the LEDControl device and sends the requests understood by this
device.
This program must be linked with libusb on Unix and libusb-win32 on Windows.
See http://libusb.sourceforge.net/ or http://libusb-win32.sourceforge.net/
respectively.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <usb.h>

#include "../firmware/globals.h"   /* custom request numbers */

#include "ledcube.c"

/**
 * 
 */
void eeprom1()
{

    unsigned long buf = 0;
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

        // lc_set animation stop
        lc_setMode(MODE_ANIMATION_STOP);

        // lc_set the frame to save
        lc_setFrame(buf);

        // save to position tmp
        //lc_saveFrame(buf, tmp);

        // lc_set mode to animate endless loop
        lc_setMode(MODE_ANIMATION_LOOP);
    }

}

void sinus1(int max)
{

    // lc_set animation stop
    lc_setMode(MODE_ANIMATION_STOP);

    int j = max;
    while (--j)
    {

        int i = 0;
        int k = 0;
        for (i = 0; i < 360; i+=11)
        //for (i = 0; i < 360; i++)
        {
            // 2 = 27
            // 1 = 27 / 2
            // n = 27 * n / 2
            double d = cos((double)((6.28*i)/360)) + 1; // 6.28 = PI * 2
            unsigned long tmp = (1 << (int)((27 * d) / 2));


            //printf("%d\t%f\t%d\t%d\n", i, d, high, low);

            // show frame
            lc_setFrame(tmp);
            // or save the frame to eeprom
            //tmp = tmp + (k << 27);
            //if (k < 32)
                //lc_saveFrame(tmp, k);

            usleep(2500);
            k++;
        }

    }

}

/**
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

    lc_init();

    demo();

    lc_setMode(MODE_ANIMATION_LOOP);

    lc_close();

    return 0;
}

