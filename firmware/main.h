//  Mini-LED-Cube 1.0
//
//  Copyright (C) 2009 Paul Wilhelm <paul@mosfetkiller.de>
//  http://mosfetkiller.de/?s=miniledcube
//
//  Changed by Kai Lauterbach (klaute at web dot de)

//    Interner RC-Oszillator, CKDIV8 Disabled

#ifndef __main_h__
#define __main_h__

#define F_CPU 12000000UL

//    Includes
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
//#include <avr/wdt.h>

//    Bitpopelei
#define    set_bit(var, bit)    ((var) |= (1 << (bit)))
#define    clear_bit(var, bit)    ((var) &= (unsigned)~(1 << (bit)))

//    Bool
#define FALSE    0
#define TRUE    1

//    Definitionen
#define PIXEL_TON    30
#define PIXEL_TOFF    10

//    Cube-Array
unsigned char cube[3][3][3];
unsigned char buffer[3][3][3];    //    Framebuffer

//    Prototypen
void init(void);

extern void init_usb(void);
extern void usbPoll(void);

/*
//    Programmzähler
unsigned int program_counter = 0;

//    Framezähler
volatile unsigned char frame_counter = 0, fps = 0;


//    Pixelmakros
#define PSET(x,y,z)        (0b01000000 | ((z * 3 + x) + y * 9))
#define PCLEAR(x,y,z)    (0b00000000 | ((z * 3 + x) + y * 9))

//    Instructions
#define CLEAR    0b10000000
#define SET        0b10010000
#define FPS        0b10110000
#define NEXT    0b11110000

//    Variablen
#define VAR_FPS    0

//    Für CLEAR und SET
#define CLEAR_ALL    0
#define SET_ALL        0

//    Für NEXT
#define JUMP_FORWARD    1
#define JUMP_BACKWARD    2


// Animation in pgmspace
const prog_char program_1[] =
{
    FPS, 10,

    CLEAR, SET + 12, NEXT, CLEAR, SET + 14, NEXT,    //    Vor- und zurück tanzen
    CLEAR, SET + 12, NEXT, CLEAR, SET + 14, NEXT,
    CLEAR, SET + 12, NEXT, CLEAR, SET + 15, NEXT,
    CLEAR, SET + 12, NEXT, CLEAR, SET + 15,

    FPS, 5, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,    //    Umdrehung
    FPS, 5, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    FPS, 6, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,
    FPS, 6, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    FPS, 7, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,
    FPS, 7, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    FPS, 8, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,
    FPS, 8, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    FPS, 9, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,
    FPS, 9, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    FPS, 10, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,
    FPS, 10, CLEAR, SET + 2, NEXT, CLEAR, SET + 15, NEXT,
    CLEAR, SET + 8, NEXT, CLEAR, SET + 12, NEXT,    //    Umfallen
    CLEAR, SET + 4, NEXT, CLEAR, SET + 5, NEXT, CLEAR, SET + 6, NEXT,    //    Ebenen
    CLEAR, SET + 1, NEXT, CLEAR, SET + 2, NEXT, CLEAR, SET + 3, NEXT,
    CLEAR, SET + 7, NEXT, CLEAR, SET + 8, NEXT, CLEAR, SET + 9, NEXT,

    FPS, 10,    //    Außen langlaufen

    CLEAR,
    PSET(0,0,0), PSET(1,0,0), PSET(0,1,0), PSET(1,1,0), PSET(0,2,0), PSET(1,2,0), NEXT,
    PCLEAR(0,0,0), PSET(2,0,0), PCLEAR(0,1,0), PSET(2,1,0), PCLEAR(0,2,0), PSET(2,2,0), NEXT,
    PCLEAR(1,0,0), PSET(2,0,1), PCLEAR(1,1,0), PSET(2,1,1), PCLEAR(1,2,0), PSET(2,2,1), NEXT,
    PCLEAR(2,0,0), PSET(2,0,2), PCLEAR(2,1,0), PSET(2,1,2), PCLEAR(2,2,0), PSET(2,2,2), NEXT,
    PCLEAR(2,0,1), PSET(1,0,2), PCLEAR(2,1,1), PSET(1,1,2), PCLEAR(2,2,1), PSET(1,2,2), NEXT,
    PCLEAR(2,0,2), PSET(0,0,2), PCLEAR(2,1,2), PSET(0,1,2), PCLEAR(2,2,2), PSET(0,2,2), NEXT,
    PCLEAR(1,0,2), PSET(0,0,1), PCLEAR(1,1,2), PSET(0,1,1), PCLEAR(1,2,2), PSET(0,2,1), NEXT,
    PCLEAR(0,0,2), PSET(0,0,0), PCLEAR(0,1,2), PSET(0,1,0), PCLEAR(0,2,2), PSET(0,2,0), NEXT,
    PCLEAR(0,0,1), PCLEAR(0,1,1), PCLEAR(0,2,1),

    SET + 7, NEXT, CLEAR, SET + 8, NEXT, CLEAR, SET + 9, NEXT,
    CLEAR, SET + 8, NEXT, CLEAR, SET + 7, NEXT,
};

const prog_char *program_pointer = program_1;
unsigned int program_length = sizeof(program_1);
*/
#endif // __main_h__

