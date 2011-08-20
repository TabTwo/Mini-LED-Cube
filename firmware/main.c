//	Mini-LED-Cube 1.0
//
//	Copyright (C) 2009 Paul Wilhelm <paul@mosfetkiller.de>
//	http://mosfetkiller.de/?s=miniledcube

//	Interner RC-Oszillator, CKDIV8 Disabled
#define F_CPU 8000000UL

//	Includes
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

//	Bitpopelei
#define	set_bit(var, bit)	((var) |= (1 << (bit)))
#define	clear_bit(var, bit)	((var) &= (unsigned)~(1 << (bit)))

//	Bool
#define FALSE	0
#define TRUE	1

//	Definitionen
#define PIXEL_TON	30
#define PIXEL_TOFF	10

//	Cube-Array
unsigned char cube[3][3][3];
unsigned char buffer[3][3][3];	//	Framebuffer

//	Prototypen
void init();

//	Programmzähler
unsigned int program_counter = 0;

//	Framezähler
volatile unsigned char frame_counter = 0, fps = 0;


//	Pixelmakros
#define PSET(x,y,z)		(0b01000000 | ((z * 3 + x) + y * 9))
#define PCLEAR(x,y,z)	(0b00000000 | ((z * 3 + x) + y * 9))

//	Instructions
#define CLEAR	0b10000000
#define SET		0b10010000
#define FPS		0b10110000
#define NEXT	0b11110000

//	Variablen
#define VAR_FPS	0

//	Für CLEAR und SET
#define CLEAR_ALL	0
#define SET_ALL		0

//	Für NEXT
#define JUMP_FORWARD	1
#define JUMP_BACKWARD	2


//	Programmcode
const prog_char program_1[] =
{
	FPS, 10,

	CLEAR, SET + 12, NEXT, CLEAR, SET + 14, NEXT,	//	Vor- und zurück tanzen
	CLEAR, SET + 12, NEXT, CLEAR, SET + 14, NEXT,
	CLEAR, SET + 12, NEXT, CLEAR, SET + 15, NEXT,
	CLEAR, SET + 12, NEXT, CLEAR, SET + 15,

	FPS, 5, CLEAR, SET + 8, NEXT, CLEAR, SET + 14, NEXT,	//	Umdrehung
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
	CLEAR, SET + 8, NEXT, CLEAR, SET + 12, NEXT,	//	Umfallen
	CLEAR, SET + 4, NEXT, CLEAR, SET + 5, NEXT, CLEAR, SET + 6, NEXT,	//	Ebenen
	CLEAR, SET + 1, NEXT, CLEAR, SET + 2, NEXT, CLEAR, SET + 3, NEXT,
	CLEAR, SET + 7, NEXT, CLEAR, SET + 8, NEXT, CLEAR, SET + 9, NEXT,

	FPS, 10,	//	Außen langlaufen

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


//	Main
int main(void)
{
	//	Initialisierung
	init();

	//	Hauptschleife
	while (1)
	{
		unsigned char instruction = pgm_read_byte(&(program_pointer[program_counter]));

		if ((instruction & 0b10000000) == 0)
		//	Pixel
		{
			unsigned char coord = instruction & 0b00111111;	//	Uns interessieren nur die 6 untersten Bits

			unsigned char y = coord / 9;
			unsigned char x = (coord - y * 9) % 3;
			unsigned char z = (coord - y * 9) / 3;
			buffer[x][y][z] = (instruction & 0b01000000) / 0b01000000;
		}
		else
		//	Instruction
		{
			unsigned char operation = instruction & 0b11110000;	//	Uns interessieren nur die 4 obersten Bits

			if (operation == CLEAR || operation == SET)
			{
				unsigned char frame = instruction & 0b00001111;

				//	Folgende Werte entsprechen SET_ALL
				unsigned char x_min = 0, x_max = 3, y_min = 0, y_max = 3, z_min = 0, z_max = 3;

				//	Folgendes kann noch optimiert werden.

				//	Y-Z-Ebene (links, mitte, rechts)
				if (frame == 1) { x_min = 0; x_max = 1; }
				if (frame == 2) { x_min = 1; x_max = 2; }
				if (frame == 3) { x_min = 2; x_max = 3; }

				//	X-Z-Ebene (unten, mitte, oben)
				if (frame == 4) { y_min = 0; y_max = 1; }
				if (frame == 5) { y_min = 1; y_max = 2; }
				if (frame == 6) { y_min = 2; y_max = 3; }

				//	X-Y-Ebene (hinten, mitte, vorne)
				if (frame == 7) { z_min = 0; z_max = 1; }
				if (frame == 8) { z_min = 1; z_max = 2; }
				if (frame == 9) { z_min = 2; z_max = 3; }

				if (frame < 10)
				{
					for (unsigned char z = z_min; z < z_max; z++)
						for (unsigned char y = y_min; y < y_max; y++)
							for (unsigned char x = x_min; x < x_max; x++)
								if (operation == SET) buffer[x][y][z] = 1; else buffer[x][y][z] = 0;
				} else
				{
					for (unsigned char a = 0; a < 3; a++)
						for (unsigned char b = 0; b < 3; b++)
						{
							unsigned char x = 0, y = 0, z = 0;

							if (frame == 10) { x = a; y = b; z = b; }			//	Unten hinten nach oben vorne
							if (frame == 11) { x = a; y = a; z = b; }			//	Unten links nach oben rechts
							if (frame == 12) { x = a; y = b; z = 2 - b; }		//	Unten vorne nach oben hinten
							if (frame == 13) { x = a; y = 2 - a; z = b; }		//	Oben links nach unten rechts
							if (frame == 14) { x = b; y = a; z = b; }			//	Hinten links nach vorne rechts
							if (frame == 15) { x = a; y = 2 - b; z = 2 - a; }	//	Vorne links nach hinten rechts

							if (operation == SET) buffer[x][y][z] = 1; else buffer[x][y][z] = 0;
						}
				}
			} else

			if (operation == FPS)
			{
				if (program_counter + 1 < program_length) program_counter++; //	else: Fehler
				unsigned char byte = pgm_read_byte(&(program_pointer[program_counter]));

				fps = byte;
			} else

			if (operation == NEXT)
			{
				//	VAR_FPS = 0: Frame nicht zeichnen, keine Wartezeit
				if (fps > 0)
				{
					//	Temporäres Array ins "echte" Array kopieren
					for (unsigned char z = 0; z < 3; z++)
						for (unsigned char y = 0; y < 3; y++)
							for (unsigned char x = 0; x < 3; x++)
								cube[x][y][z] = buffer[x][y][z];

					for (unsigned char i = 0; i < fps; i++)
					{
						_delay_ms(5);
					}
				}
			}

		}

		//	Programmzähler erhöhen, bzw. bei Erreichen des Programmendes wieder von vorn beginnen
		if (program_counter + 1 < program_length) program_counter++; else program_counter = 0;
	}
}


//	Initialisierung
void init()
{
	//	Ports vorbereiten
	DDRB =	0b11111111;	//	PB0-PB7: LED 1-8 (Kathoden)
	PORTB =	0b11111111;	//	HIGH

	DDRD =	0b1111000;	//	PD6: LED 9 (Kathode); PD5-PD3: A-C (Anoden)
	PORTD =	0b1000000;

	//	Timer-Interrupt "TIMER1" vorbereiten
	cli();

	set_bit(TIMSK, OCIE1A);
	set_bit(TCCR1B, WGM12);

	//	Animations-Geschwindigkeit
	OCR1AH = 0x01;
	OCR1AL = 0x00;

	clear_bit(TCCR1B, CS12);	//	Prescaler 64
	set_bit(TCCR1B, CS11);
	set_bit(TCCR1B, CS10);

	sei();
}


//	Interruptvektor von TIMER1
SIGNAL(SIG_OUTPUT_COMPARE1A)
{
	//	Pixel multiplexen
	for (unsigned char z = 0; z < 3; z++)
	{
		for (unsigned char y = 0; y < 3; y++)
		{
			for (unsigned char x = 0; x < 3; x++)
			{
				unsigned char n = z * 3 + x;

				//	LED an
				if (cube[x][y][z] == 1)
				{
					if (n < 8) clear_bit(PORTB, n); else clear_bit(PORTD, 6);
					set_bit(PORTD, y + 3);
				}
				//	ON-Time
				for (unsigned long i = 0; i < PIXEL_TON; i++) { asm volatile("nop"::); }

				//	LED aus
				if (cube[x][y][z] == 1)
				{
					clear_bit(PORTD, y + 3);
					if (n < 8) set_bit(PORTB, n); else set_bit(PORTD, 6);
				}
				//	OFF-Time
				for (unsigned long i = 0; i < PIXEL_TOFF; i++) { asm volatile("nop"::); }
			}
		}
	}
}
