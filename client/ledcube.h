
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

void lc_setFrame(unsigned long);
void lc_setMode(int);
void lc_saveFrame(unsigned long, int);
void lc_init(void);
void lc_close(void);

