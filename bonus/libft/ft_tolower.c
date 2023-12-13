
#include "../headers/libft.h"

/**
 * Convert a character to lowercase if it is an uppercase letter.
 *
 * @param c The character to be converted.
 *
 * @return The lowercase equivalent of the character if it is an uppercase
 *         letter, otherwise the character itself is returned.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
