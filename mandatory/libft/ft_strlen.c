
#include "../headers/libft.h"

/**
 * Calculate the length of a string.
 *
 * @param str The input string.
 *
 * @return The length of the string, excluding the null-terminator.
 */
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
