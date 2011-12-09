/*  CTHN.de MiniLEDCube
 *
 *  Kai Lauterbach (klaute at web dot de)
 *
 *  Based on http://mosfetkiller.de/?s=miniledcube
 *
 *  License: General Public License (GPL v3)
 *
 */

#include "main.h"

// Main
int __attribute__((OS_main))
main()
{
    // Initialisierung
    init();
    init_usb();

    // Hauptschleife
    for (;;)
    {
        usbPoll(); // keep connected
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

    set_bit(TIMSK, OCIE1A); // Interrupt für ISR COMPA
    //set_bit(TCCR1B, WGM12); // Überlauf wird unten gesetzt

    // Animations-Geschwindigkeit
    // (vergleichswert bei dem der Interrupt ausgelöst wird)
    // 625d = 0x271 = 0b00000010, 0b01110001
    OCR1AH = 0b00000010;
    OCR1AL = 0b01110001;

    // anpassen auf reihenweise ausgabe
    // Vorteiler durch 64 (0x011) ----> CS12=0, CS11=1, CS10=1
    //clear_bit(TCCR1B, CS12);    // Prescaler 64
    //set_bit(TCCR1B, CS11);
    //set_bit(TCCR1B, CS10);
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);

    sei(); // Set enable interrupt bit (Muss gesetzt werden damit es überhaupt aufgerufen wird)
}

// Interruptvektor von TIMER1
ISR (TIMER1_COMPA_vect)
{

	// PORTD = __, 9, C, B, A,D+,D-,__
    PORTD &= 0b10000111; // 7tes Bit löschen (Leitung 9) und alle Ebenen deaktivieren
    PORTD |= (1 << 6) | ((1 << cube_level) << 3); // cube_level setzen (Ebene A=0, B=1, C=2)

    uint32_t tmp = cube_level * 9;

    // PORTB = 1..8
    // 0 = leuchtet, 1 = leuchtet nicht (invertiert!)
    PORTB = ~((cube >> tmp) & 0xff);

    if ( (((cube >> tmp) >> 8) & 0x01) )
        PORTD &= ~(1 << 6); // 9. led setzen falls notwendig

    cube_level++;
    if (cube_level > 2) cube_level = 0;

}

