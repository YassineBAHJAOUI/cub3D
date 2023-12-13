
#include "../headers/libft.h"

/**
 * Write a single character to the standard output.
 *
 * @param c The character to be written.
 *
 * @return On success, the number of bytes written is returned.
 *         On error, -1 is returned.
 */
int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
