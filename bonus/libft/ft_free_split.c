
#include "../headers/libft.h"

/**
 * Frees the memory allocated for an array of strings.
 *
 * @param split  The array of strings to be freed.
 */
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
