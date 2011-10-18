#define F_CPU 12000000UL

// Bitpopelei
#define    set_bit(var, bit)    ((var) |= (1 << (bit)))
#define    clear_bit(var, bit)  ((var) &= (unsigned)~(1 << (bit)))

// Bool
#define FALSE   0
#define TRUE    1

// Definitionen
#define PIXEL_TON    30
#define PIXEL_TOFF   10

#define sleep_nop(cnt)   for (uint8_t i = 0; i < cnt; i++) { asm volatile("nop"::); }

// Pixelmakros
#define PSET(x,y,z)      (0b01000000 | ((z * 3 + x) + y * 9))
#define PCLEAR(x,y,z)    (0b00000000 | ((z * 3 + x) + y * 9))

// Instructions
#define CLEAR   0b10000000
#define SET     0b10010000
#define FPS     0b10110000
#define NEXT    0b11110000

// Variablen
#define VAR_FPS    0

// Für CLEAR und SET
#define CLEAR_ALL    0
#define SET_ALL      0

// Für NEXT
#define JUMP_FORWARD    1
#define JUMP_BACKWARD   2

