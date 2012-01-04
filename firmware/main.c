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

#include "main.h"

/*! \brief Main loop
 */
int __attribute__((OS_main)) main()
{
    // Initialize the AVR and the USB connection.
    init();
    init_usb();

    // Hauptschleife
    for (;;)
    {
        usbPoll(); // keep connected
    }
}

/*! \brief Initialize the AVR.
 */
void init()
{
    // Init ports
    DDRB  = 0b11111111;    // PB0-PB7: LED 1-8 (Kathode)
    PORTB = 0b11111111;    // HIGH

    DDRD  = 0b01111000;    // PD6: LED 9 (Kathode); PD5-PD3: A-C (Anode)
    PORTD = 0b01000000;

    // Setup Timer-Interrupt "TIMER1" compare match interrupt
    TIMSK |= (1 << OCIE1A);

    // Refreshrate is 100Hz of the whole LEDCube.
    // The ISR comes up at 300Hz.
    // Set the compare value to
    // 625d = 0x271 = 0b00000010, 0b01110001
    OCR1AH = 0b00000010;
    OCR1AL = 0b01110001;

    // Set prescale to 64 and clear the counter on compare match.
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);

    sei(); // Enable interrupts global
}

/*! \brief TIMER1 interruptvector, called in a frequency of 300Hz.
 */
ISR (TIMER1_COMPA_vect)
{

    if ( !(--delay) ) // decrease the counter and check if we are done with waiting
    {
        if (frmnum == MAX_EEPROM_FRAMES)
        {
            if (mode == MODE_ANIMATION_SINGLE)
                mode = MODE_ANIMATION_STOP; // stop the animation after we have reached the 31th frame
            frmnum = 0; // always start at the first frame
        } else {
            if (mode)
            {
                // if we are in an animation mode we have to load a frame out of the eeprom
                // and increase the counter
                frame = eeprom_read_dword( &eep_anim[frmnum] );
                frmnum++;
            }
        }
        // Just shift right by 24 instead of 27 to multiply the delay by 8.
        // Possible delays are 8 16 24 32 and so on. A zero delay isn't possible.
        // Zero means that a delay of 255 happens because the delay variable was decreased first before testing
        // it's is zero value.
        delay = (frame >> 24) & 0xf8;
    }

	// PORTD = __, 9, C, B, A,D+,D-,__
    PORTD &= 0b10000111; // delete bit 3 to 6 (bit 3 to 5 = layer 0 to 2; bit 6 = wire 9 to the LEDs)
    PORTD |= (1 << 6) | ((1 << level) << 3); // set the current level and pin 6 to high (9th LEDs off)

    uint8_t tmp = level * 9; // calculate the position in the frame

    // PORTB = 1..8
    // 0 = led is on, 1 = led is off
    PORTB = ~((frame >> tmp) & 0xff);

    if ( (((frame >> tmp) >> 8) & 0x01) )
        PORTD &= ~(1 << 6); // turn the 9th LED on if required

    // rotate through the 3 level
    level++;
    if (level > 2) level = 0;

}

