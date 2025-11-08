#include "lumen.h"

void    init_lighting(void)
{
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);
}

void    set_lighting(int one, int two, int three, int four)
{
    init_lighting();
    if (one)
        PORTB |= (1 << PORTB0);
    if (two)
        PORTB |= (1 << PORTB1);
    if (three)
        PORTB |= (1 << PORTB2);
    if (four)
        PORTB |= (1 << PORTB4);
    _delay_ms(20);
    PORTB &= ~(1 << PORTB0);
    PORTB &= ~(1 << PORTB1);
    PORTB &= ~(1 << PORTB2);
    PORTB &= ~(1 << PORTB4);
}