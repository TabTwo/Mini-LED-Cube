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

    set_bit(TIMSK, OCIE1A);
    set_bit(TCCR1B, WGM12);

    // Animations-Geschwindigkeit
    // (vergleichswert bei dem der Interrupt ausgelöst wird)
    OCR1AH = 0x01;
    OCR1AL = 0x00;

    // anpassen auf reihenweise ausgabe
    clear_bit(TCCR1B, CS12);    // Prescaler 64
    set_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);

    sei();
}

// Interruptvektor von TIMER1
//SIGNAL(SIG_OUTPUT_COMPARE1A) // alte schreibweise
ISR (TIMER1_COMPA_vect)
{

    // Alle Pins von PORTD auf LOW setzen
    // Höchstes Bit in PORTA auf 0 setzen (Leitung 9 für letzte Reihe)

    // bei cube_row_offset % 3 eine Ebene weiter schalten (ABC-Leitungen durch rotieren)
    // bei Systemstart muss A aktiviert sein.

    // bits der anzuzeigenden reihe auslesen (cube & (0b00000111 << cube_row_offset))
    // und in PORTD und Pin 8 von PORTA setzen

    // cube_row_offset += 3 // immer um 3 Bits weiter springen in 32Bit Variable

    // cube_row_offset auf 0 setzen wenn maximum überschritten (27-3 = 24)

}

