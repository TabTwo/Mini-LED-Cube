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

    uint8_t anim = 0;

    // Hauptschleife
    //while (1)
    for (;;)
    {
        //wdt_reset(); // we are alive, so don't reset the µC
        usbPoll(); // keep connected

        // hier pause einfügen
        _delay_ms(50); // beispielsweise 50 ms => muss angepasst werden an usb kommunikation

        anim++;

        if (anim == 40)
        {
            if (cube == 0xffffffff)
                cube = 0x07007007;
            else if (cube == 0x07007007)
                cube = 0x00000000;
            else if (cube == 0x00000000)
                cube = 0xffffffff;
            anim = 0;
        }

    }
}

// Initialisierung
void init()
{
    // Ports vorbereiten
    DDRB  =    0b11111111;    // PB0-PB7: LED 1-8 (Kathoden)
    PORTB =    0b11111111;    // HIGH

    DDRD  =    0b01111000;    // PD6: LED 9 (Kathode); PD5-PD3: A-C (Anoden)
    PORTD =    0b01000000;

    // Timer-Interrupt "TIMER1" vorbereiten
    //cli(); //

    set_bit(TIMSK, OCIE1A); // Interrupt für ISR COMPA
    set_bit(TCCR1B, WGM12); // Überlauf

    // Animations-Geschwindigkeit
    // (vergleichswert bei dem der Interrupt ausgelöst wird)
    // 625d = 0x271 = 0b00000010, 0b01110001
    OCR1AH = 0b00000010;
    OCR1AL = 0b01110001;

    // anpassen auf reihenweise ausgabe
    // Vorteiler durch 64 (0x011) ----> CS12=0, CS11=1, CS10=1
    clear_bit(TCCR1B, CS12);    // Prescaler 64
    set_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);



    sei(); // Set enable interrupt bit (Muss gesetzt werden damit es überhaupt aufgerufen wird)
}

// Interruptvektor von TIMER1
//SIGNAL(SIG_OUTPUT_COMPARE1A) // alte schreibweise
ISR (TIMER1_COMPA_vect)
{
    // PORTD = __, 9, C, B, A,D+,D-,__
    PORTD &= 0b10000111; // 7tes Bit löschen (Leitung 9) und alle Ebenen deaktivieren
    PORTD |= ((1 << cube_level) << 3); // cube_level setzen (Ebene A=0, B=1, C=2)

    uint32_t tmp  = cube_level * 9;
    uint32_t tmp1 = tmp + 8;

    // PORTB = 1..8
    // 0 = leuchtet, 1 = leuchtet nicht (invertiert!)
    //PORTB = ~((uint32_t)(cube & (0b11111111 << tmp)) >> tmp);
    //PORTB = ((uint32_t)(~cube & (uint32_t)(0xff << tmp)) >> tmp);
    PORTB = ~((cube >> tmp) & 0xff);

    // PORTD &= 0b10111111; // bereits oben erledigt
    //PORTD |= ~(((uint32_t)(cube & (1 << (tmp+8))) >> (tmp+8)) << 6);
    //PORTD |= (((~cube & (1 << tmp)) >> tmp) << 6);
    if ( (((cube >> tmp) >> 8) & 0x01) == 1 )
        PORTD &= ~(1 << 6);
    else
        PORTD |= (1 << 6);
    //PORTD |= (1 << 6); // test to always off

    cube_level++;
    if (cube_level > 2) cube_level = 0;
}

