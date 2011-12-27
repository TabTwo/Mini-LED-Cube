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

#include "ledcube.h"

/*! \brief The setFrame function.
 * \param frame The 32bit frame data. Bit 0-8 equals layer one; bit 9 - 17 euqals layer two; bit 18 - 26 equals layer three. the 5 MSB is the lifetime of the current frame in ISR calls (300Hz).
 * \return NOT_CONNECTED_ERROR or the return value of the usb_control_msg function.
 */
int lc_setFrame(unsigned long frame)
{

    if (_lc_handle == NULL)
        return NOT_CONNECTED_ERROR;

    int low  =  frame & 0xffff;
    int high = (frame & 0xffff0000) >> 16;

    int ret = usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME,  low, 0, _lc_buffer, 0, 300);
    ret += usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_FRAME, high, 1, _lc_buffer, 0, 300);

    return ret;
}

/*! \brief The setMode function.
 * \param mode The firmware mode. MODE_ANIMATION_STOP; MODE_ANIMATION_SINGLE; MODE_ANIMATION_LOOP
 * \return NOT_CONNECTED_ERROR or the return value of the usb_control_msg function.
 */
int lc_setMode(int mode)
{
    if (_lc_handle == NULL)
        return NOT_CONNECTED_ERROR;

    return usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_SET_MODE, mode, 0, _lc_buffer, 0, 300);
}

/*! \brief The saveFrame function.
 * \param frame The 32bit frame data. Bit 0-8 equals layer one; bit 9 - 17 euqals layer two; bit 18 - 26 equals layer three. The 5 MSB is the lifetime of the current frame in ISR calls (300Hz) multiplied by 8.
 * \param delay The lifetime (onyl 5 bits) of the given frame in ISR calls multiplied by 8.
 * \param index The position in the EEPROM (0 to 31) of the internal animation content.
 * \return NOT_CONNECTED_ERROR or the return value of the usb_control_msg function.
 */
int lc_saveFrame(unsigned long frame, int delay, int index)
{
    if (_lc_handle == NULL)
        return NOT_CONNECTED_ERROR;

    frame = frame + (delay << 27);

    lc_setFrame(frame);

    return usb_control_msg(_lc_handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, CUSTOM_RQ_EEPROM_STORE_FRAME, 0, index, _lc_buffer, 0, 300);
}

/*! \brief The init function.
 * \return SUCCESSFULLY_CONNECTED or DEVICE_NOT_FOUND_ERROR.
 */
int lc_init()
{

    usb_init();

    /* compute lc_vid/lc_pid from usbconfig.h so that there is a central source of information */
    _lc_vid = _lc_rawVid[1] * 256 + _lc_rawVid[0];
    _lc_pid = _lc_rawPid[1] * 256 + _lc_rawPid[0];

    /* The following function is in opendevice.c: */
    if( usbOpenDevice( &_lc_handle, _lc_vid, _lc_vendor, _lc_pid, _lc_product, NULL, NULL, NULL) != 0)
    {
        fprintf(stderr, "Could not find USB device \"%s\" with lc_vid=0x%x lc_pid=0x%x\n", _lc_product, _lc_vid, _lc_pid);
        return DEVICE_NOT_FOUND_ERROR;
    }
    return SUCCESSFULLY_CONNECTED;
}

/*! \brief The close function.
 * \return NOT_CONNECTED_ERROR or return state of the usb_close function.
 */
int lc_close()
{
    if (_lc_handle == NULL)
        return NOT_CONNECTED_ERROR;

    return usb_close(_lc_handle);

}

