#include "lumen.h"

void    init_rgb(void)
{
    DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6); // Configurer PD3, PD5 et PD6 comme sorties pour les LEDs
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
}

void    set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r; // Rouge sur OC0A (PB3)
    OCR0A = g; // Vert sur OC0B (PB4)
    OCR2B = b; // Bleu sur OC2B (PD3)
}