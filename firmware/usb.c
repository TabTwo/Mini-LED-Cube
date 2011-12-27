/* 
 * CTHN.de MiniLEDCube
 *
 *  usb.h by Kai Lauterbach 11/2011
 *
 *  Based on project: hid-custom-rq example by Christian Starkjohann
 *  Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 *
 *  License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 *
 */

#include "usb.h"

/* ------------------------------------------------------------------------- */

/*! \brief
 *  \param data USB Data packet.
 *  \return The length of the received or send data.
 */
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data;

    if ( (rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR )
    {
        if ( rq->bRequest == CUSTOM_RQ_SET_FRAME )
        {

            // because of the code size we have to transfer one frame in
            // two steps (control messages)
            if ( ! rq->wIndex.bytes[0] )
            {
                // the lower word
                frame = (frame & (uint32_t)0xffff0000) |
                       ( rq->wValue.bytes[0] +
                        (rq->wValue.bytes[1] << 8) );
            } else {
                // the high word
                frame = (frame & (uint32_t)0x0000ffff) |
                       ((uint32_t)( rq->wValue.bytes[0] +
                                   (rq->wValue.bytes[1] << 8) ) << 16);
            }

        } else if ( rq->bRequest == CUSTOM_RQ_EEPROM_STORE_FRAME )
        {
            // save the actual frame to the eeprom
            // don't forget to send a frame first
            eeprom_write_dword( &eep_anim[ rq->wIndex.bytes[0] ], frame );

        } else if ( rq->bRequest == CUSTOM_RQ_SET_MODE )
        {
            // set the firmware mode
            // 0 = stop; 1 = single; 2 = loop
            mode = rq->wValue.bytes[0];
        }

    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

/*! \brief Initializes the USB conneciton.
 */
void init_usb(void)
{

    uint8_t i;

    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */

    // fake USB disconnect for > 250 ms
    while(--i)
    {
        asm volatile("nop"::);
    }

    usbDeviceConnect();

}

/* ------------------------------------------------------------------------- */
