#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB0);
    PORTD |= (1 << PORTD2);

    while (1)
    {
        if (PIND & (1 << PIND2))
        {
            // Bouton pressé → LED ON (active-low)
            PORTB &= ~(1 << PORTB0);
            _delay_ms(20); // anti-rebond simple
        }
        else
        {
            // Bouton relâché (selon câblage) → LED OFF (active-low)
            PORTB |= (1 << PORTB0);
            _delay_ms(20); // anti-rebond simple
        }
    }
    return(0);
}