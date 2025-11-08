#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    RGB(int RED, int GREEN, int BLUE)
{
    if (RED)
        PORTD |= (1 << PORTD5); // Allumer LED rouge
    else
        PORTD &= ~(1 << PORTD5); // Éteindre LED rouge

    if (GREEN)
        PORTD |= (1 << PORTD6); // Allumer LED verte
    else
        PORTD &= ~(1 << PORTD6); // Éteindre LED verte

    if (BLUE)
        PORTD |= (1 << PORTD3); // Allumer LED bleue
    else
        PORTD &= ~(1 << PORTD3); // Éteindre LED bleue
    _delay_ms(1000);
}

int main(void)
{
    DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6); // Configurer PD3, PD5 et PD6 comme sorties pour les LEDs
    while (1)
    {
        RGB(1, 0, 0); // Rouge
        RGB(0, 1, 0); // Vert
        RGB(0, 0, 1); // Bleu
        RGB(1, 1, 0); // Jaune
        RGB(0, 1, 1); // Cyan
        RGB(1, 0, 1); // Magenta
        RGB(1, 1, 1); // Blanc
    }
    return(0);
}