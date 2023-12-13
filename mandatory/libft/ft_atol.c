
#include "../headers/libft.h"

/**
 * Converts a string representation of a long integer to its corresponding
 * long integer value.
 *
 * @param str The string to convert to a long integer.
 * @return The converted long integer value.
 */
long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(((int)*str)))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
