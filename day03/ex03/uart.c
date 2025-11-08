#include "lumen.h"

void    USART_init(void) 
{
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Active RX et TX
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

