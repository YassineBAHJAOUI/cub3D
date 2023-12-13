
#include "../headers/libft.h"

/**
 * Print an integer to the standard output.
 *
 * @param nb The integer to be printed.
 *
 * @return The total number of characters printed.
 */
int	ft_putnbr(long long nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789";
	if (nb < 0)
	{
		nb *= -1;
		count += ft_putchar('-');
	}
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
