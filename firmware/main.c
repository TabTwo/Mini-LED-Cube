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
ISR (TIMER1_COMPA_vect)
{

	PORTD &= 0xC7; // 0b11000111
	PORTD |= (1 << (cube_layer + 3)); // shift "1" to bit 3,4,5 in PortD
	PORTB = ~(cube & (0xFF << (cube_layer * 9))); // set the lines 1 to 8 negated to the port b
	PORTD = (~(cube & (1 << cube_layer * 9 + 8)) << 6)
	        | (PORTD & 0x7F); // 0b01111111 keep the ower 7 bits and set the 9. bit from the LEDCube data.

	cube_layer++;
	
	if (cube_layer > 2)
		cube_layer = 0;
			
}

