#include "lumen.h"

void	*ft_memset(void *s, int c, int n)
{
	char	*arr;

	arr = s;
	while (n-- > 0)
	{
		*arr++ = (char)c;
	}
	return (s);
}

void    ft_error(const char *msg)
{
    while (*msg)
    {
        UART_tx(*msg);
        msg++;
    }
}

int isPrintbble(char c)
{
    if (c >= 32 && c <= 126)
    {
        return (1);
    }
    return (0);
}

char    whileSpace(char c)
{
    while (c == ' ' || c == '\t')
    {
        UART_tx(c);
        c = UART_rx();
        if (c != ' ' && c != '\t')
            break ;
    }
    return (c);
}