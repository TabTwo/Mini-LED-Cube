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

        // hier pause einfügen
        _delay_ms(50); // beispielsweise 50 ms => muss angepasst werden an usb kommunikation

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
    PORTD &= 0b11000111; // Reset durch Bitmaske
    PORTD |= ((1 << (cube_level))<< 3); // Level setzen (A=0, B=1, C=2)

    // PORTB = 1..8
    // 0 = leuchtet, 1 = leuchtet nicht (invertiert!)
    PORTB = ~(cube & (0b11111111 << (cube_level*9)));

    PORTD &= 0b10111111; // 7tes Bit löschen (9)
    PORTD |= ~((cube & (1 << (cube_level*9+8))) << 6);

    //cube_level++;
    //if (cube_level > 2) cube_level = 0;
}

