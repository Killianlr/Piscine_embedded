#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    TIMER1_COMPA_vect(void) __attribute__ ((signal));

void    init_rgb(void)
{
    DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6); // Configurer PD3, PD5 et PD6 comme sorties pour les LEDs

    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // Fast PWM, non-inverting mode compare on OC0A and OC0B
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); // compare on OC2B, Fast PWM non-inverting mode
    TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024

    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTC, Prescaler 64 pour Timer1
    TCCR1A = 0;
    TIMSK1 = (1 << OCIE1A);
    OCR1A = 4999; 
}

void    set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = r; // Rouge sur OC0A (PB3)
    OCR0B = g; // Vert sur OC0B (PB4)
    OCR2B = b; // Bleu sur OC2B (PD3)
}

void wheel(uint8_t pos) 
{
    pos = 255 - pos;
    if (pos < 85) {
        set_rgb(255 - pos * 3, 0, pos * 3);
    } else if (pos < 170) {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    } else {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

void    TIMER1_COMPA_vect(void)
{
    static uint8_t i = 0;
    if (i < 255)
        i++;
    else
        i = 0;
    wheel(i);
}

int main(void)
{
    init_rgb();
    sei();
    while(1) {}
    return(0);
}