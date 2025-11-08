#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6); // Configurer PD3, PD5 et PD6 comme sorties pour les LEDs
    while (1)
    {
        PORTD = (1 << PORTD5); // Allumer LED sur PB1
        _delay_ms(1000);
        PORTD = (1 << PORTD6); // Allumer LED sur PB2
        _delay_ms(1000);
        PORTD = (1 << PORTD3); // Allumer LED sur PB0
        _delay_ms(1000);
    }
    return(0);
}