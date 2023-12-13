
#include "../headers/libft.h"

/**
 * Compare two strings up to a specified number of characters.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n  The maximum number of characters to compare.
 *
 * @return An integer value less than, equal to, or greater than zero if the
 *         first `n` characters of `s1` are found, respectively, to be less
 *         than, to match, or be greater than the first `n` characters of `s2`.
 *         The comparison is case-sensitive.
 */
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
