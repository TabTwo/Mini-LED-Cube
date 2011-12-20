/* 
 * CTHN.de MiniLEDCube
 *
 *  usb.c by Kai Lauterbach 11/2011
 *
 *  Based on project: hid-custom-rq example by Christian Starkjohann
 *  Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 *
 *  License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 *
 */

#ifndef __usb_h__
#define __usb_h__

#include <avr/eeprom.h>

#ifndef EEMEM
#define EEMEM  __attribute__ ((section (".eeprom")))
#endif

#include "globals.h"

#include "usbconfig.h"
#include "usbdrv.h"
#include "requests.h"       /* The custom request numbers we use */

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

void init_usb(void);

//extern uint8_t eep_delay_max EEMEM;
extern uint32_t eep_anim[MAX_EEPROM_FRAMES] EEMEM;

// usb buffer
extern uint32_t     frame; // Framebuffer
extern uint8_t       mode; // FW mode

#endif // __usb_h__

