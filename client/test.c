/* Name: set-led.c
 * Project: hid-custom-rq example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-10
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: set-led.c 692 2008-11-07 15:07:40Z cs $
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
#include <usb.h>        /* this is libusb */

#include "opendevice.h" /* common code moved to separate module */

#include "../firmware/requests.h"   /* custom request numbers */
#include "../firmware/usbconfig.h"  /* device's VID/PID and names */

int main(int argc, char **argv)
{
	usb_dev_handle      *handle = NULL;
	const unsigned char rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
	char                vendor[] = {USB_CFG_VENDOR_NAME, 0}, product[] = {USB_CFG_DEVICE_NAME, 0};
	char                buffer[4];
	int                 vid, pid;

    usb_init();

    /* compute VID/PID from usbconfig.h so that there is a central source of information */
    vid = rawVid[1] * 256 + rawVid[0];
    pid = rawPid[1] * 256 + rawPid[0];
    /* The following function is in opendevice.c: */
    if(usbOpenDevice(&handle, vid, vendor, pid, product, NULL, NULL, NULL) != 0){
        fprintf(stderr, "Could not find USB device \"%s\" with vid=0x%x pid=0x%x\n", product, vid, pid);
        exit(1);
    }
    /* Since we use only control endpoint 0, we don't need to choose a
     * configuration and interface. Reading device descriptor and setting a
     * configuration and interface is done through endpoint 0 after all.
     * However, newer versions of Linux require that we claim an interface
     * even for endpoint 0. Enable the following code if your operating system
     * needs it: */
#if 0
    int retries = 1, usbConfiguration = 1, usbInterface = 0;
    if(usb_set_configuration(handle, usbConfiguration) && showWarnings){
        fprintf(stderr, "Warning: could not set configuration: %s\n", usb_strerror());
    }
    /* now try to claim the interface and detach the kernel HID driver on
     * Linux and other operating systems which support the call. */
    while((len = usb_claim_interface(handle, usbInterface)) != 0 && retries-- > 0){
#ifdef LIBUSB_HAS_DETACH_KERNEL_DRIVER_NP
        if(usb_detach_kernel_driver_np(handle, 0) < 0 && showWarnings){
            fprintf(stderr, "Warning: could not detach kernel driver: %s\n", usb_strerror());
        }
#endif
    }
#endif

    //usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_EEPROM, 0, 0, buffer, 0, 300);
    //usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_EEPROM_SET_FRAME, 0, 1, buffer, 0, 300);
    //sleep(1);
    //usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_EEPROM_SET_FRAME, 0, 0, buffer, 0, 300);
    //sleep(1);

    // int usb_control_msg(usb_dev_handle *dev, int requesttype, int request, int value, int index, char *bytes, int size, int timeout);
    // 32 bit in 2 transmission
    //printf("clear\n");
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x0000, 0, buffer, 0, 300);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x0000, 1, buffer, 0, 300);

    //sleep(1);

    //printf("test 1\n");
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x7347, 0, buffer, 0, 300);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x0712, 1, buffer, 0, 300);

    //sleep(1);

    //printf("test 2\n");
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x7007, 0, buffer, 0, 300);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x0700, 1, buffer, 0, 300);

    //sleep(1);

    //printf("full\n");
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0xffff, 0, buffer, 0, 300);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0x07ff, 1, buffer, 0, 300);

    //sleep(1);
    int low_last  = 0;
    int high_last = 0;
int j = 0xffff;
while (--j)
{

    int i = 0;
    for (i = 0; i < 360; i++)
//    for (i = 79; i < 90; i++)
    {
        // 2 = 27
        // 1 = 27 / 2
        // n = 27 * n / 2
        double d = cos((double)((6.28*i)/360)) + 1; // 6.28 = PI * 2
        unsigned long tmp = (1 << (int)((27 * d) / 2));
        int low  =  tmp & 0x0000ffff;
        int high = (tmp & 0xffff0000) >> 16;

        printf("%d\t%f\t%d\t%d\n", i, d, high, low);

        if (low > 0 && low_last != low)
        {
            usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, low,  0, buffer, 0, 300);
            if (high == 0)
                usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0, 1, buffer, 0, 300);
        }
        if (high > 0 && high_last != high)
        {
            usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, high, 1, buffer, 0, 300);
            if (low == 0)
                usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, 0, 0, buffer, 0, 300);
        }

        high_last = high;
        low_last = low;

        usleep(2500);
    }

}


    usb_close(handle);
    return 0;
}
