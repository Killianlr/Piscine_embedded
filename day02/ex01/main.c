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

void    Clock_init(void)
{
    TCCR1A = 0; // Mode normal
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, préscaler = 1024
    OCR1A = 31248; // Pour une interruption toutes les 1s à 16MHz avec prescaler 1024
    TIMSK1 = (1 << OCIE1A); // Activer l'interruption sur comparaison
}

void    UART_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit prêt
    UDR0 = c ; // Envoyer le caractère 'Z'
}

void    uart_printstr(const char *str)
{
    while (*str)
    {
        UART_tx(*str++);
    }
    UART_tx('\r');
}

ISR(TIMER1_COMPA_vect)
{
    uart_printstr("Hello, World!\n");
}

int main(void)
{
    UART_init();
    Clock_init();
    sei(); // Activer les interruptions globales
    while (1) {}
    return(0);
}