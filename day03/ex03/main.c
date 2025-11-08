#include "lumen.h"

char prompt[8];
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

static int hex_val(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

int parse_hex_color(const char *s, uint8_t *r, uint8_t *g, uint8_t *b)
{
    const char *p;
    if (!s)
        return 1;

    p = s;
    int hi, lo;
    hi = hex_val(p[0]); 
    if (hi < 0) 
        return 1;
    lo = hex_val(p[1]); 
    if (lo < 0) 
        return 1;
    *r = (uint8_t)((hi << 4) | lo);

    hi = hex_val(p[2]); 
    if (hi < 0) 
        return 1;
    lo = hex_val(p[3]); 
    if (lo < 0) 
        return 1;
    *g = (uint8_t)((hi << 4) | lo);

    hi = hex_val(p[4]); 
    if (hi < 0) 
        return 1;
    lo = hex_val(p[5]); 
    if (lo < 0) 
        return 1;
    *b = (uint8_t)((hi << 4) | lo);

    return 0;
}

void    getHexa(char *hex, int i)
{
    if (hex[0] != '#')
        ft_error("MISSING '#'     \r\n");
    else if (i != 7)
        ft_error("WRONG HEXA CODE       \r\n");
    else if (parse_hex_color(++hex, &red, &green, &blue))
    {
        ft_error("WRONG HEXA CODE       \r\n");
        red = blue = green = 0;
    }
}

void    getPrompt(void)
{
    static char c;
    int i = 0;

    while (1)
    {
        c = UART_rx();
        if (i == 0 || i > 6)
            c = whileSpace(c);
        if (isPrintbble(c))
        {
            if (i < 7)
                prompt[i] = c;
            i++;
            set_lighting(1, 0, 0, 0);
        }
        if ((c == '\b' || c == 127) && i > 0)
        {
            prompt[i] = 0;
            i--;
            UART_tx('\b');
            UART_tx(' ');
            UART_tx('\b');
            // set_lighting(0, 1, 0, 0);
        }
        if (c == '\r' || c == '\n')
        {
            UART_tx('\r');
            UART_tx('\n');
            getHexa(prompt, i);
            break ;
        }
        else
            UART_tx(c);
    }
}

int main(void)
{
    USART_init();
    while (1)
    {
        ft_memset(prompt, 0, 8);
        getPrompt();
        init_rgb();
        set_rgb(red, green, blue);
    }
    return(0);
}