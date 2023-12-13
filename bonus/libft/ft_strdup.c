
#include "../headers/libft.h"

/**
 * Duplicate a string.
 *
 * @param str The string to be duplicated.
 *
 * @return A pointer to the newly allocated duplicate string.
 *         If memory allocation fails, it returns NULL.
 */
char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (0);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
