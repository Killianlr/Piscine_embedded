#include <avr/io.h>
#include <util/delay.h>

#define PRESS 1
#define RELEASE 0

uint16_t calc_icr1 (uint16_t prescaler_value)
{
    // Calcul de ICR1 pour une fréquence de 1 Hz
    // f_pwm = f_clk / (prescaler * (1 + TOP))  => TOP = (f_clk / (prescaler * f_pwm)) - 1
    const uint32_t F_CLK = 16000000; // Fréquence d'horloge en Hz
    uint16_t icr1 = (F_CLK / (prescaler_value * 1)) - 1;
    return icr1;
}
int main(void)
{

    // Configuration
    DDRB |= (1 << DDB1); // PB1 en sortie (LED connectée à OC1A)
    TCCR1A = (1 << COM1A1) | (1 << WGM11); // Non-inverting PWM on OC1A (Clear OC1A on Compare, set at BOTTOM)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12); // Fast PWM mode 14 (WGM13:WGM12 = 1,1) + prescaler = 256 (CS12)


    ICR1 = calc_icr1(256); // TOP pour 1 Hz avec préscaler 1024
    const uint16_t step = ICR1 / 10; // 10% de la période
    uint16_t duty_value = step;

    uint8_t sw1_curr_state = RELEASE;
    uint8_t sw2_curr_state = RELEASE;

    while (1) 
    {
        if (!(PIND & (1 << PIND2)))
            sw1_curr_state = PRESS;
        if (!(PIND & (1 << PIND4)))
            sw2_curr_state = PRESS;
        if (sw1_curr_state == PRESS && PIND & (1 << PIND2))
        {
            if (duty_value < (ICR1 - step))
                duty_value += step;
            sw1_curr_state = RELEASE;
        }
        if (sw2_curr_state == PRESS && PIND & (1 << PIND4))
        {
            if (duty_value > step)
                duty_value -= step;
            sw2_curr_state = RELEASE;
        }
        OCR1A = duty_value;
        _delay_ms(20); // Anti-rebond
    }
    return 0;
}