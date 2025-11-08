#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB1); // PB1 en sortie (LED connectée)
    TCCR1A = (1 << COM1A0); // Toggle OC1A on Compare Match

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Mode CTC, préscaler = 1024

    /*
     * f_clk = 16 000 000 Hz, prescaler = 1024, f_out = 1 Hz
     * OCR1A = (16e6 / (2 * 1024 * 1)) - 1 = 7812
     */
    OCR1A = 7812;

    while (1) {}

    return 0;
}