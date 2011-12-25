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

#ifndef __LEDCUBE_H_INCLUDED__
#define __LEDCUBE_H_INCLUDED__

#define NOT_CONNECTED_ERROR    -1
#define DEVICE_NOT_FOUND_ERROR -2

#define SUCCESSFULLY_CONNECTED  1

#include <stdio.h>
#include <usb.h>        /* this is libusb */

#include "opendevice.h" /* common code moved to separate module */

#include "../firmware/globals.h"   /* custom request numbers */
#include "../firmware/requests.h"   /* custom request numbers */
#include "../firmware/usbconfig.h"  /* device's VID/PID and names */

usb_dev_handle      *_lc_handle = NULL;

const unsigned char  _lc_rawVid[2] = {USB_CFG_VENDOR_ID},
                     _lc_rawPid[2] = {USB_CFG_DEVICE_ID};

char                 _lc_vendor[]  = {USB_CFG_VENDOR_NAME, 0},
                     _lc_product[] = {USB_CFG_DEVICE_NAME, 0};

char                 _lc_buffer[4];

int                  _lc_vid,
                     _lc_pid;

int lc_setFrame(unsigned long);
int lc_setMode(int);
int lc_saveFrame(unsigned long, int);
int lc_init(void);
int lc_close(void);

#endif // __LEDCUBE_H_INCLUDED__

