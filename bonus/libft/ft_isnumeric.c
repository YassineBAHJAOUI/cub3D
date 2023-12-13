
#include "../headers/libft.h"

/**
 * Checks if the given string represents a numeric value.
 *
 * @param str The string to check.
 * @return 1 if the string represents a numeric value, 0 otherwise.
 */
int	ft_isnumeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
