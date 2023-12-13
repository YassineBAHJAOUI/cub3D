
#include "../headers/libft.h"

/**
 * Checks if the given character is an alphabetic character.
 *
 * @param c The character to check.
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
