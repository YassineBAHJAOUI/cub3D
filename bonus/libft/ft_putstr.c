
#include "../headers/libft.h"

/**
 * Write a string to the standard output.
 *
 * @param str The string to be written.
 *
 * @return The total number of characters written.
 *         If the string is NULL, it also writes "(null)" and returns the count.
 */
int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		ft_putchar(*str);
		count++;
		str++;
	}
	return (count);
}
