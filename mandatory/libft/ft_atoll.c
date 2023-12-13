
#include "../headers/libft.h"

/**
 * Converts a string representation of a long long integer to its corresponding
 * long long integer value.
 *
 * @param str The string to convert to a long long integer.
 * @return The converted long long integer value.
 */
long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

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
