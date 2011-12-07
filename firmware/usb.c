/* Name: usb.h by Kai Lauterbach
 * Based on Project: hid-custom-rq example
 * Revision: $Id: main.c 790 2010-05-30 21:00:26Z cs $
 * Author: Christian Starkjohann
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#include "usb.h"

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data;

    if ( (rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR )
    {
        if ( rq->bRequest == CUSTOM_RQ_SET_STATUS )
        {

            if ( rq->wIndex.bytes[0] == 27 )
            {
                cube = (cube & (uint32_t)0xffff0000) |
                        rq->wValue.bytes[0] +
                       (rq->wValue.bytes[1] << 8);
            } else if ( rq->wIndex.bytes[0] == 28 )
            {
                cube = (cube & (uint32_t)0x0000ffff) |
                       ((uint32_t)(rq->wValue.bytes[0] +
                        (rq->wValue.bytes[1] << 8)) << 16);
            } else if ( rq->wIndex.bytes[0] < 27 )
            {
                if ( rq->wValue.bytes[0] == 1 )
                    cube |= ((uint32_t)1 << rq->wIndex.bytes[0]);
                else
                    cube &= ~((uint32_t)1 << rq->wIndex.bytes[0]);
            }

        //} else if ( rq->bRequest == CUSTOM_RQ_GET_STATUS ) {
            // Send one byte to the USB host.

            //static uchar dataBuffer[1];     // buffer must stay valid when usbFunctionSetup returns
            //usbMsgPtr = 0;         // tell the driver which data to return
            //return 1;                       // tell the driver to send 1 byte

            //return 0;                       // tell the driver to send 0 byte
        }
    //} else {
        /* class requests USBRQ_HID_GET_REPORT and USBRQ_HID_SET_REPORT are
         * not implemented since we never call them. The operating system
         * won't call them either because our descriptor defines no meaning.
         */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

void init_usb(void)
{
    uchar i;

    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */

    i = 0;
    while(--i) {             /* fake USB disconnect for > 250 ms */
        //wdt_reset();
        _delay_ms(1);
        //sleep_nop(255);
    }

    usbDeviceConnect();

    sei(); // enable global interrupts

}

/* TODO add to the projects main

    init_usb();

    // Even if you don't use the watchdog, turn it off here. On newer devices,
    // the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
    //
    // RESET status: all port bits are inputs without pull-up.
    // That's the way we need D+ and D-. Therefore we don't need any
    // additional hardware initialization.
    wdt_enable(WDTO_1S);

    ...mainloop start...

        wdt_reset(); // we are alive, please dont reset the µC (optional)
        usbPoll(); // keep the usb connection up

    ...end mainloop...


*/

/* ------------------------------------------------------------------------- */
