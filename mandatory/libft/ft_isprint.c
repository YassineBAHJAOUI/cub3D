
#include "../headers/libft.h"

/**
 * Checks if the given character is a printable ASCII character.
 *
 * @param c The character to check.
 * @return 1 if the character is printable, 0 otherwise.
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}
