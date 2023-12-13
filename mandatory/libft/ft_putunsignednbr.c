
#include "../headers/libft.h"

/**
 * Print an unsigned integer to the standard output.
 *
 * @param nb The unsigned integer to be printed.
 *
 * @return The total number of characters printed.
 */
int	ft_putunsignednbr(unsigned int nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789";
	if (nb < 10)
	{
		count += ft_putchar(base[nb]);
	}
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	return (count);
}
