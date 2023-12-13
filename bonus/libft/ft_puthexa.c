
#include "../headers/libft.h"

/**
 * Print the hexadecimal representation of a given number.
 *
 * @param nb The number to be converted to hexadecimal.
 * @param c  The case of the hexadecimal digits
 * ('x' for lowercase, 'X' for uppercase).
 *
 * @return The total number of characters printed.
 */
int	ft_puthexa(unsigned long nb, char c)
{
	int		count;
	char	*base;

	count = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (nb < 16)
	{
		count += ft_putchar(base[nb]);
	}
	if (nb >= 16)
	{
		count += ft_puthexa(nb / 16, c);
		count += ft_puthexa(nb % 16, c);
	}
	return (count);
}
