#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void INT0_vect(void) __attribute__ ((signal));

int unpressed = 1;

void INT0_vect(void)
{
    if (EICRA & (1 << ISC01) && !(EICRA & (1 << ISC00))) // Check if falling edge triggered
    {
        PORTB ^= (1 << PB0); // Toggle PB0
        EICRA ^= (1 << ISC00);
    }
    else
        unpressed = 0;
}

int main(void)
{
    DDRB |= (1 << PB0); // Set PB0 as output
    EIMSK |= (1 << INT0); // Enable external interrupt INT0
    EICRA |= (1 << ISC01); // Trigger INT0 on falling edge
    sei();
    while (1){
        _delay_ms(50);
        if (!unpressed)
        {
            unpressed = 1;
            EICRA ^= (1 << ISC00); // Toggle edge detection
        }
    }
    return 0;
}