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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <usb.h>
#include <argtable2.h>

#include "../firmware/globals.h"   /* custom request numbers */

#include "ledcube.c"

int main(int argc, char **argv)
{
    lc_init();

    // TODO

    lc_close();
}

