#include <avr/io.h>
int main(void)
{
    DDRB |= (1 << DDB1);

    const unsigned long DELAY_COUNT = 250000;

    while (1)
    {
        PORTB ^= (1 << PORTB1);

        volatile unsigned long i;
        for (i = 0; i < DELAY_COUNT; ++i)
        {
            asm volatile("nop");
        }
    }
    return(0);
}