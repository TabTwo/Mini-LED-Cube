
#include "ledcube.h"

void lc_setFrame(unsigned long frame)
{

    int low  =  frame & 0xffff;
    int high = (frame & 0xffff0000) >> 16;

    usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME,  low, 0, _lc_buffer, 0, 300);
    usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, high, 1, _lc_buffer, 0, 300);
}

void lc_setMode(int mode)
{
    usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_MODE, mode, 0, _lc_buffer, 0, 300);
}

void lc_saveFrame(unsigned long frame, int index)
{
    lc_setFrame(frame);

    usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_EEPROM_STORE_FRAME, 0, index, _lc_buffer, 0, 300);
}

void lc_init()
{

    usb_init();

    /* compute lc_vid/lc_pid from usbconfig.h so that there is a central source of information */
    _lc_vid = _lc_rawVid[1] * 256 + _lc_rawVid[0];
    _lc_pid = _lc_rawPid[1] * 256 + _lc_rawPid[0];

    /* The following function is in opendevice.c: */
    if( usbOpenDevice( &_lc_handle, _lc_vid, _lc_vendor, _lc_pid, _lc_product, NULL, NULL, NULL) != 0)
    {

        fprintf(stderr, "Could not find USB device \"%s\" with lc_vid=0x%x lc_pid=0x%x\n", _lc_product, _lc_vid, _lc_pid);
    }
}

void lc_close()
{
    usb_close(_lc_handle);

}

