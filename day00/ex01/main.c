#include <avr/io.h>


int main(void)
{
    // Autre façon: utiliser _BV() et les noms de bits
    DDRB |= (1 << DDB0); // passe le bit 0 du port B en sortie (valeur 1) ne change pas les autres bits
    PORTB |= (1 << PORTB0); // met le bit 0 du port B à 1 (allume la LED) ne change pas les autres bits
    return(0);
}