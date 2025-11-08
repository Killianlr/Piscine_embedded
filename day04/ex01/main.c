#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    TIMER0_COMPA_vect(void) __attribute__ ((signal));

uint16_t duty_cycle = 0;
uint16_t flag = 0;

void TIMER0_COMPA_vect(void)
{
    if (flag == 0)
        OCR1A += 250;
    if (flag == 1)
        OCR1A -= 250;
    if (OCR1A == ICR1)
        flag = 1;
    if (OCR1A == 0)
        flag = 0;
}

void    config_timer0()
{
    // Non-inverting PWM on OC2A (Clear OC2A on Compare, set at BOTTOM)
    // Timer/counter0 should trigger interrupt 100 / 200 times per second
    TCCR0A = (1 << COM0A0) | (1 << WGM01);
    TCCR0B = (1 << CS02) | (1 << CS00);// prescaler = 1024
    OCR0A = 78; // for 100 Hz 

    TIMSK0 = (1 << OCIE0A); // Enable Timer/Counter0 Output Compare Match A Interrupt
}

void    config_timer1()
{
    // Non-inverting PWM on OC1A (Clear OC1A on Compare, set at BOTTOM)
    TCCR1A = (1 << COM1A1) | (1 << WGM11); 

    // Fast PWM mode 14 (WGM13:WGM12 = 1,1) + prescaler = 8 (CS12 and CS10)
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);

    // TOP pour 80 Hz
    ICR1 = 25000;
    // // 10% duty cycle
    // OCR1A = 0;
}

int main(void)
{
    DDRB |= (1 << DDB1); // PB1 en sortie (LED connectée à OC1A)

    config_timer1();

    config_timer0();

    sei();
    while (1) {}
    return (0);
}