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
        /*if ( rq->bRequest == CUSTOM_RQ_SET_LED )
        {
            if ( rq->wValue.bytes[0] == 1 )
                cube |= ((uint32_t)1 << rq->wIndex.bytes[0]);
            else
                cube &= ~((uint32_t)1 << rq->wIndex.bytes[0]);
        } else*/ if ( rq->bRequest == CUSTOM_RQ_SET_FRAME )
        {

            /* requires more flash space
            cube = (cube & (uint32_t)0xffff0000) |
                             ( rq->wValue.bytes[0] + (rq->wValue.bytes[1] << 8) ) |
                             ( (uint32_t)(rq->wIndex.bytes[0] + (rq->wIndex.bytes[1] << 8)) << 16 );*/
            if ( rq->wIndex.bytes[0] == 0 )
            {
                frame = (frame & (uint32_t)0xffff0000) |
                       ( rq->wValue.bytes[0] +
                        (rq->wValue.bytes[1] << 8) );
            } else {
                frame = (frame & (uint32_t)0x0000ffff) |
                       ((uint32_t)( rq->wValue.bytes[0] +
                                   (rq->wValue.bytes[1] << 8) ) << 16);
            }

        } else if ( rq->bRequest == CUSTOM_RQ_EEPROM_STORE_FRAME )
        {
            eeprom_write_dword(&eep_anim[0], 0x07007007);
        } else if ( rq->bRequest == CUSTOM_RQ_EEPROM_SET_FRAME )
        {
            frame = eeprom_read_dword( &eep_anim[rq->wIndex.bytes[0]] );
        }

    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

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
