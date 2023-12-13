
#include "../headers/libft.h"

/**
 * Convert a character to uppercase if it is a lowercase letter.
 *
 * @param c The character to be converted.
 *
 * @return The uppercase equivalent of the character if it is a lowercase
 *         letter, otherwise the character itself is returned.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
