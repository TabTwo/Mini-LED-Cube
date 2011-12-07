#define F_CPU 12000000UL

// Bitshifting
#define    set_bit(var, bit)    ((var) |= (1 << (bit)))
#define    clear_bit(var, bit)  ((var) &= (unsigned)~(1 << (bit)))

#define sleep_nop(cnt)   for (uint8_t i = 0; i < cnt; i++) { asm volatile("nop"::); }

