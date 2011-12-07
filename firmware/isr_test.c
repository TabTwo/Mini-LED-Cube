
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int PORTD = 0xff;
    int PORTB = 0xff;
    int cube = 0x000001ff;
    int cube_level = 0;

    char test[100];

    int i = 0;
    for (i = 0; i < 3; i++)
    {

    printf("-----------------\ncube_level = %d\n",cube_level);

    printf("PORTD = 0x%2x\n", PORTD);
    printf("PORTB = 0x%2x\n", PORTB);

    PORTD &= 0x87; // 0x87 = 0b10000111; // 7tes Bit löschen (Leitung 9) und alle Ebenen deaktivieren

    printf("& 0b10000111: PORTD = 0x%2x\n", PORTD);

    PORTD |= ((1 << cube_level)<< 3); // cube_level setzen (Ebene A=0, B=1, C=2)

    printf("Level festlegen: PORTD = 0x%2x\n", PORTD);

    int tmp = cube_level * 9;

    printf("8 Bits aus cube: PORTD = 0x%2x\n", ((~cube & (0xff << tmp)) >> tmp));
    // PORTB = 1..8
    // 0 = leuchtet, 1 = leuchtet nicht (invertiert!)
    PORTB = ((~cube & (0xff << tmp)) >> tmp);

    printf("Pins1-8: PORTB = 0x%2x\n", PORTB);

    // PORTD &= 0b10111111; // bereits oben erledigt
    PORTD |= (((~cube & (1 << (tmp+8))) >> (tmp+8)) << 6);

    printf("Pin9: PORTD = 0x%2x\n", PORTD);

    cube_level++;
    if (cube_level > 2) cube_level = 0;

    }

}

