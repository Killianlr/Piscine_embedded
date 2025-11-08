#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 8ul))) - 1)

void    UART_init(void) 
{
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Active RX et TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8 bits, 1 stop, pas de parité
    UCSR0A = (1 << U2X0); // Double la vitesse de transmission
}

void    Clock_init(void)
{
    TCCR1A = 0; // Mode normal
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, préscaler = 1024
    OCR1A = 156; // Pour une interruption toutes les 0.005s à 16MHz avec prescaler 1024
    TIMSK1 = (1 << OCIE1A); // Activer l'interruption sur comparaison
}

void    UART_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit prêt
    UDR0 = c ; // Envoyer le caractère 'Z'
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

ISR(TIMER1_COMPA_vect)
{
    if (UCSR0A & (1 << RXC0)) // Vérifier si des données ont été reçues
    {
        char c = UDR0; // Lire le caractère reçu
        c = (c >= 'a' && c <= 'z') ? (c - 32) : (c >= 'A' && c <= 'Z') ? (c + 32) : c; // Convertir en majuscule si minuscule
        enterBackspace(c);
        UART_tx(c); // Echo du caractère reçu
    }
}

int main(void)
{
    UART_init();
    Clock_init();
    sei(); // Activer les interruptions globales
    while (1) {}
    return(0);
}