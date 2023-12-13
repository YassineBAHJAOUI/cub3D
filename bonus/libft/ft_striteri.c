
#include "../headers/libft.h"

/**
 * Apply a function to each character of a string, along with its index.
 *
 * @param s The string to iterate over.
 * @param f The function to apply to each character, taking the index and
 * character as parameters.
 *
 * @return None.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
