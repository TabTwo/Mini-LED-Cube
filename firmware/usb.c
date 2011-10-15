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
usbRequest_t    *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR){
        if(rq->bRequest == CUSTOM_RQ_SET_STATUS){

            // receive animation data

        }else if(rq->bRequest == CUSTOM_RQ_GET_STATUS){
            //static uchar dataBuffer[1];     // buffer must stay valid when usbFunctionSetup returns
            //dataBuffer[0] = ((LED_PORT_OUTPUT & _BV(LED_BIT)) != 0);
            //usbMsgPtr = dataBuffer;         // tell the driver which data to return
            //return 1;                       // tell the driver to send 1 byte
            return 0;                       // tell the driver to send 1 byte
        }
    }else{
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
    while(--i){             /* fake USB disconnect for > 250 ms */
        //wdt_reset();
        _delay_ms(1);
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

        wdt_reset(); // we are alive, please dont reset the µC
        usbPoll(); // keep the usb connection up

    ...end mainloop...


*/

/* ------------------------------------------------------------------------- */
