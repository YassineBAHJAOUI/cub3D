
#include "../headers/libft.h"

/**
 * Checks if the given character is a quotation mark.
 *
 * @param c The character to check.
 * @return 1 if the character is a quotation mark, 0 otherwise.
 */
int	ft_isquote(int c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}
