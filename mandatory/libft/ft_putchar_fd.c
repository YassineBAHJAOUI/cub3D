
#include "../headers/libft.h"

/**
 * Write a single character to a file descriptor.
 *
 * @param c  The character to be written.
 * @param fd The file descriptor to which the character is written.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
