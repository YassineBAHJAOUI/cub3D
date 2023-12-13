
#include "../headers/libft.h"

/**
 * Write a string followed by a newline character to a file descriptor.
 *
 * @param str The string to be written.
 * @param fd  The file descriptor to which the string is written.
 */
void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}
