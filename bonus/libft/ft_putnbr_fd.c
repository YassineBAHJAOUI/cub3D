
#include "../headers/libft.h"

/**
 * Write an integer to a file descriptor.
 *
 * @param nb The integer to be written.
 * @param fd The file descriptor to which the integer is written.
 */
void	ft_putnbr_fd(int nb, int fd)
{
	long long		n;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
