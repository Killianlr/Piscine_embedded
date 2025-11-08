#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 8ul))) - 1)

void    UART_init(void) 
{
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B =  ( 1 << RXEN0) | (1 << TXEN0); // Active RX et TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8 bits, 1 stop, pas de parité
    UCSR0A = (1 << U2X0); // Double la vitesse de transmission
}

void    UART_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit prêt
    UDR0 = c ; // Envoyer le caractère 'Z'
}

char    UART_rx(void)
{
    while (!(UCSR0A & (1 << RXC0))); // Attendre la réception d'un caractère
    return UDR0; // Lire le caractère reçu
}

void    enterBackspace(char c)
{

    if (c == '\b' || c == 127) 
    {
        UART_tx('\b');
        UART_tx(' ');
        UART_tx('\b');
    }
    if (c == '\r') 
    {
        UART_tx('\n'); 
    }
}

int main(void)
{
    UART_init();
    char c;
    while (1) 
    {
        c = UART_rx();
        enterBackspace(c);
        UART_tx(c);
    }
    return(0);
}