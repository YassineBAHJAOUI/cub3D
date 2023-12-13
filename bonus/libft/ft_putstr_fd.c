
#include "../headers/libft.h"

/**
 * Write a string to a file descriptor.
 *
 * @param str The string to be written.
 * @param fd  The file descriptor to which the string is written.
 */
void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}
