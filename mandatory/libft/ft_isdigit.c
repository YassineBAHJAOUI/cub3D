
#include "../headers/libft.h"

/**
 * Checks if the given character is a decimal digit (0-9).
 *
 * @param c The character to check.
 * @return 1 if the character is a decimal digit, 0 otherwise.
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
