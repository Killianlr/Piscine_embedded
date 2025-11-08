#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);

    int count = 0;
    while (1)
    {

        if (!(PIND & (1 << PIND2)) && count <= 23)
        {
            count++;
             while (!(PIND & (1 << PIND2)))
                _delay_ms(50); // Attente relâchement avec anti-rebond
            if (count == 8)
                count += 8;
        }
        if (!(PIND & (1 << PIND4)) && count >= 1 || count == 24)
        {
            count--;
            while (!(PIND & (1 << PIND4)))
                _delay_ms(50); // Attente relâchement avec anti-rebond
            if (count == 15)
                count -= 8;
        }
        PORTB = count;
    }
    return(0);
}