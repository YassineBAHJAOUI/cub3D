
#include "../headers/libft.h"

/**
 * Checks if the given character is a valid ASCII character.
 *
 * @param c The character to check.
 * @return 1 if the character is a valid ASCII character, 0 otherwise.
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
