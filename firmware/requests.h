/* 
 * CTHN.de MiniLEDCube
 *
 *  requests.h by Kai Lauterbach
 *
 *  Based on project: hid-custom-rq example by Christian Starkjohann
 *  Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 *
 *  License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 *
 */

/* This header is shared between the firmware and the host software. It
 * defines the USB request numbers (and optionally data types) used to
 * communicate between the host and the device.
 */

#ifndef __REQUESTS_H_INCLUDED__
#define __REQUESTS_H_INCLUDED__

#define CUSTOM_RQ_SET_FRAME           1
#define CUSTOM_RQ_EEPROM_STORE_FRAME  2
#define CUSTOM_RQ_SET_MODE            3
#define CUSTOM_RQ_SET_DELAY           4

#endif /* __REQUESTS_H_INCLUDED__ */
