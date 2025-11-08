#include <avr/io.h>
#include <util/delay.h>



int main(void)
{

    DDRB |= (1 << DDB1); // PB1 en sortie (LED connectée à OC1A)

    // Non-inverting PWM on OC1A (Clear OC1A on Compare, set at BOTTOM)
    TCCR1A = (1 << COM1A1) | (1 << WGM11);

    // Fast PWM mode 14 (WGM13:WGM12 = 1,1) + prescaler = 1024 (CS12 and CS10)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10);

    /*
    * Choix : f_clk = 16 MHz, prescaler = 1024 => TOP = 16e6 / (1024 * 1) - 1 = 15624
     * ICR1 = 15624
     * OCR1A = round(0.10 * (15624 + 1)) = 1562 (≈10%)
    */

    // TOP pour 1 Hz
    ICR1 = 15624;
    // 10% duty cycle
    OCR1A = 1562;

    while (1) {}

    return 0;
}