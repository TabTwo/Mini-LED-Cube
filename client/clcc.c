/*
 * CTHN.de MiniLEDCube
 *
 *  By Kai Lauterbach (klaute at web dot de) 12/2011
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

#include "globals.h"

#include "../firmware/globals.h"

// External functions to control the ledcube.
extern void lc_setFrame(unsigned long);
extern void lc_setMode(int);
extern int  lc_saveFrame(unsigned long, int, int);
extern void lc_init(void);
extern void lc_close(void);

int main(int argc, char **argv)
{

    // parameter structures
    struct arg_lit  *param_stop   = arg_lit0("p", "stop", "stop animation");
    struct arg_lit  *param_single = arg_lit0("i", "single", "single animation");
    struct arg_lit  *param_loop   = arg_lit0("l", "loop", "loop animation");
    struct arg_int  *param_frame  = arg_int0("m", "frame", "<n>", "frame data");
    struct arg_int  *param_pos    = arg_int0("o", "pos", "<n>", "frame pos in eeprom");
    struct arg_int  *param_delay  = arg_int0("y", "delay", "<n>", "frame delay in eeprom");
    struct arg_lit  *param_save   = arg_lit0("s", "save", "save one frame to the EEPROM");
    //struct arg_lit  *param_tty    = arg_lit0("t", "terminal", "terminal mode");
    //struct arg_lit  *param_daemon = arg_lit0("d", "daemon", "daemon mode");
    struct arg_lit  *param_help   = arg_lit0("h", "help", "show help");
    struct arg_file *param_file   = arg_filen("f", "ihex-file","<file>", 0, 1, "iHex input file to write to the EEPROM");
    struct arg_end  *param_end    = arg_end(20);

    // default parameter
    param_frame->ival[0] = 0x00000000;
    param_pos->ival[0]   = 0;
    param_delay->ival[0] = 1;

    // argtable array
    void *argtable[] = {
        param_stop,
        param_single,
        param_loop,
        param_frame,
        param_pos,
        param_delay,
        param_save,
        param_file,
        //param_tty,
        //param_daemon,
        param_help,
        param_end
    };

    // parse the commandline arguments
    int nerrors = arg_parse(argc,argv,argtable);

    if (arg_nullcheck(argtable) != 0)
    {
        printf("error: insufficient memory\n");
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 0;
    }

    if (nerrors == 0 && param_help->count > 0)
    {
        printf("Usage: ./clcc <OPTIONS>\n");
        arg_print_glossary(stdout, argtable, "\t%-25s %s\n");
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 0;

    }
    // parsing failed or to less parameter given
    if (nerrors > 0
        || argc < 2
        || (param_save->count > 0 && (param_pos->count == 0 || param_delay->count == 0 || param_frame->count == 0))
       )
    {
        arg_print_errors(stdout,param_end,"clcc");
        printf("\nUsage: ./clcc <OPTIONS>\n");
        arg_print_syntaxv(stdout,argtable,"\n");
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return -1;
    }

    lc_init();

    if (param_stop->count > 0)
    {
        printf("stop animation loop\n");
        lc_setMode(MODE_ANIMATION_STOP);
    }
    else if (param_loop->count > 0)
    {
        printf("starting animation loop\n");
        lc_setMode(MODE_ANIMATION_LOOP);
    }
    else if (param_single->count > 0 )
    {
        printf("starting animation as single shot\n");
        lc_setMode(MODE_ANIMATION_SINGLE);
    }
    else if (param_save->count > 0
                && param_pos->count > 0
                && param_delay->count > 0
                && param_frame->count > 0)
    {
        lc_setMode(MODE_ANIMATION_STOP);

        int frame = param_frame->ival[0];
        int delay = param_delay->ival[0];
        int pos = param_pos->ival[0];
        printf("saving frame: index=%d delay=%d frame=0x%08x\n", pos, delay, frame);
        lc_saveFrame(frame, delay, pos);

    }
    else if (param_frame->count > 0)
    {
        lc_setMode(MODE_ANIMATION_STOP);
        int frame = param_frame->ival[0];
        printf("view frame: data=0x%08x\n", frame);
        lc_setFrame(frame);
    }

    //printf("file[%d]=%s\n",i,file->filename[i]);*/

    lc_close();

    arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));

    return 0;
}

