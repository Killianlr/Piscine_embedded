#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 8ul))) - 1)

void    UART_init(void) 
{
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1 << TXEN0); // Active TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8 bits, 1 stop, pas de parité
    UCSR0A = (1 << U2X0); // Double la vitesse de transmission
}

void    UART_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit prêt
    UDR0 = c ; // Envoyer le caractère 'Z'
}

int main(void)
{
    UART_init();
    while (1)
    {
        UART_tx('Z');
        _delay_ms(1000); // Attendre 1 seconde entre chaque envoi
    }
    return(0);
}