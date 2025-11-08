#ifndef LUMEN_H
#define LUMEN_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 8ul))) - 1)

void    USART_init(void);
void    UART_tx(char c);
char    UART_rx(void);

void	*ft_memset(void *s, int c, int n);
int     isPrintbble(char c);
void    ft_error(const char *msg);
char    whileSpace(char c);

void    set_lighting(int one, int two, int three, int four);

void    init_rgb(void);
void    set_rgb(uint8_t r, uint8_t g, uint8_t b);


#endif