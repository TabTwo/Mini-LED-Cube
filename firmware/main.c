/*
 *  Based on the code of the Mini-LED-Cube 1.0
 *
 *  Copyright (C) 2009 Paul Wilhelm <paul@mosfetkiller.de>
 *  http: *mosfetkiller.de/?s=miniledcube
 *
 *  Changed by Kai Lauterbach (klaute at web dot de)
 */

#include "main.h"

// Main
int main(void)
{
    // Initialisierung
    init();
    init_usb();

    // Hauptschleife
    //while (1)
    for (;;)
    {
        //wdt_reset(); // we are alive, so don't reset the µC
        usbPoll(); // keep connected

    }
}

// Initialisierung
void init()
{
    // Ports vorbereiten
    DDRB  =    0b11111111;    // PB0-PB7: LED 1-8 (Kathoden)
    PORTB =    0b11111111;    // HIGH

    DDRD  =    0b1111000;    // PD6: LED 9 (Kathode); PD5-PD3: A-C (Anoden)
    PORTD =    0b1000000;

    // Timer-Interrupt "TIMER1" vorbereiten
    //cli(); //

    set_bit(TIMSK, OCIE1A);
    set_bit(TCCR1B, WGM12);

    // Animations-Geschwindigkeit
    OCR1AH = 0x01;
    OCR1AL = 0x00;

    clear_bit(TCCR1B, CS12);    // Prescaler 64
    set_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);

    sei();
}

// Interruptvektor von TIMER1
SIGNAL(SIG_OUTPUT_COMPARE1A)
{

    // Pixel multiplexen
    for (uint8_t z = 0; z < 3; z++)
    {
        for (uint8_t y = 0; y < 3; y++)
        {
            for (uint8_t x = 0; x < 3; x++)
            {
                uint8_t n = z * 3 + x;

                // LED an
                if (cube[x][y][z] == 1)
                {
                    if (n < 8) clear_bit(PORTB, n); else clear_bit(PORTD, 6);
                    set_bit(PORTD, y + 3);
                }
                // ON-Time
                sleep_nop(PIXEL_TON);

                // LED aus
                if (cube[x][y][z] == 1)
                {
                    clear_bit(PORTD, y + 3);
                    if (n < 8) set_bit(PORTB, n); else set_bit(PORTD, 6);
                }
                // OFF-Time
                sleep_nop(PIXEL_TOFF)
            }
        }
    }

}

